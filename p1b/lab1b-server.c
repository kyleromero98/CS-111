// NAME: Kyle Romero
// EMAIL: kyleromero98@gmail.com
// ID: 204747283

#include <getopt.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <signal.h>
#include <wait.h>
#include <zlib.h>

#define BUFSIZE 256
#define STDIN 0
#define STDOUT 1
#define STDERR 2

pid_t shellPid;
int socketFd, acceptFd;
static int forkedShell = 0;

// global flags
static int receivedPort = 0;
static int compressFlag = 0;
static int debugFlag = 0;

// called on exit; restores any problems
void restoreAndExit () {
  int status, result;
  if (forkedShell) {
    if ((result = waitpid(shellPid, &status, 0)) == -1) {
      fprintf(stderr, "WaitPid Error: Failure to wait for shell to close, %s\n\r", strerror(errno));
      exit(1);
    } else if (result == shellPid) {
      fprintf(stderr, "SHELL EXIT SIGNAL=%d STATUS=%d\n\r", (status & 0x007f), WEXITSTATUS(status));
    }
  }
  shutdown(socketFd, 0);
  shutdown(acceptFd, 0);
}

// closes a file descriptor with error checking
void closeFd (int fd) {
  if (close(fd) == -1) {
    fprintf(stderr, "I/O Error: Failure to close file descriptor, %s\n\r", strerror(errno));
    exit(1);
  }
}

// will dup a FD with error checking
void dupFd (int fd) {
  if (dup(fd) == -1) {
    fprintf(stderr, "I/O Error: Failure to dup file descriptor, %s\n\r", strerror(errno));
    exit(1);
  }
}

// creates a pipe with error checking
void createPipe(int fds[2]) {
  if (pipe(fds) == -1) {
    fprintf(stderr, "Pipe Error: Failure creating pipe, %s\n\r", strerror(errno));
    exit(1);
  }
}

// wrapper function for write
void writeBytes (int fd, const void *buf, size_t bytes) {
  if (write(fd, buf, bytes) < 0) {
    fprintf(stderr, "I/O Error: Unable to write %s, %s\n\r", (char*)buf, strerror(errno));
    exit(1);
  }
}

void def (char* src, unsigned long int src_len, char* dest, uLong* dest_len) {
  z_stream defstream;
  defstream.zalloc = Z_NULL;
  defstream.zfree = Z_NULL;
  defstream.opaque = Z_NULL;

  defstream.avail_in = (uInt) src_len;
  defstream.next_in = (Bytef *) src;
  defstream.avail_out = (uInt) *dest_len;
  defstream.next_out = (Bytef *) dest;

  deflateInit(&defstream, Z_BEST_COMPRESSION);
  deflate(&defstream, Z_FINISH);
  deflateEnd(&defstream);

  *dest_len = (uInt) ((char*) defstream.next_out - dest);

  if (debugFlag) {
    fprintf(stderr, "Deflated strlen: %lu\n\r", strlen(dest));
    fprintf(stderr, "Deflated: %s\n\r", dest);
    fprintf(stderr, "Deflated Size: %lu\n\r", *dest_len);
  }
}

void inf (char* src, uLong* src_len, char* dest, uLong* dest_len) {
  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;

  infstream.avail_in = (uInt)(*src_len);
  infstream.next_in = (Bytef *) src;
  infstream.avail_out = (uInt)(*dest_len);
  infstream.next_out = (Bytef *) dest;

  inflateInit(&infstream);
  inflate(&infstream, Z_NO_FLUSH);
  inflateEnd(&infstream);

  if (debugFlag) {
    fprintf(stderr, "Inflated strlen is: %lu\n\r", strlen(dest));
    fprintf(stderr, "Inflated string is: %s\n\r", dest);
    fprintf(stderr, "Inflated Size: %lu\n\r", *dest_len);
  }
}

void flushBuffer(int fromFd, int toFd) {
  char buf[BUFSIZE];
  char outBuf[(BUFSIZE*2)+1];
  int bytesRead;
  while ((bytesRead = read(fromFd, buf, BUFSIZE)) > 0) {
    memset(outBuf, 0, (BUFSIZE * 2) + 1);
    for (int i = 0; i < bytesRead; i++) {
      if (buf[i] == 0x0A) {
	outBuf[strlen(outBuf)] = 0x0D;
	outBuf[strlen(outBuf)] = 0x0A;
      } else {
	outBuf[strlen(outBuf)] = buf[i];
      }
    }
    if (compressFlag) {
      char sentCompress[(BUFSIZE * 2) + 1];
      uLong length = (BUFSIZE * 2) + 1;
      memset(sentCompress, 0, (BUFSIZE * 2) + 1);
      def(outBuf, length, sentCompress, &length);
      memset(outBuf, 0, (BUFSIZE * 2) + 1);
      strcpy(outBuf, sentCompress);
    }
    writeBytes(toFd, outBuf, (BUFSIZE * 2) + 1);
  }
  if (bytesRead < 0) {
    fprintf(stderr, "I/O Error: Unable to read from client, %s\n\r", strerror(errno));
    exit(1);
  }
}

int main (int argc, char** argv) {
  // on exit
  atexit(restoreAndExit);

  // START OPTION HANDLING
  // init options                                                                                                                                                                                                                         
  static struct option longOptions[] =
    {
      {"port", required_argument, NULL, 'p'},
      {"compress", no_argument, &compressFlag, 1},
      {"debug", no_argument, &debugFlag, 1},
      {0, 0, 0, 0}
    };

  int portNumber;

  int status;
  int statusIndex = 0;
  while (1) {
    status = getopt_long(argc, argv, "", longOptions, &statusIndex);

    if (status == -1)
      break;

    switch (status) {
    case 0:
      // do nothing, enters on flag argument
      break;
    case 'p':
      portNumber = atoi(optarg);
      receivedPort = 1;
      break;
    case '?':
      fprintf(stderr, "Unrecognized Option: Valid Options: --port=[port number] --log\n\r Proper usage: ./lab1b-client --port=1234 --log\n\r");
      exit(1);
    default:
      fprintf(stderr, "Option Error: Reached default case for option input with status %d\n", status);
      exit(1);
    }
  }

  if (!receivedPort) {
    fprintf(stderr, "Option Error: Expected --port=[port number] option\n Usage: ./lab1b-client --port=1234\n\r");
    exit(1);
  }
  // END OPTION HANDLING

  int socketFd;
  struct sockaddr_in server;

  if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "Socket Error: Unable to create socket, %s\n\r", strerror(errno));
    exit(1);
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(portNumber);

  if (bind(socketFd, (struct sockaddr *) &server, sizeof(server)) == -1) {
    fprintf(stderr, "Bind Error: Unable to bind socket to server, %s\n\r", strerror(errno));
    exit(1);
  }

  if (listen(socketFd, 1) == -1) {
    fprintf(stderr, "Listen Error: Unable to mark socket for listening, %s\n\r", strerror(errno));
    exit(1);
  }

  int acceptFd;
  if ((acceptFd = accept(socketFd, (struct sockaddr *) NULL, NULL)) == -1) {
    fprintf(stderr, "Accept Error: Unable to accept socket signal, %s\n\r", strerror(errno));
    exit(1);
  }

  // declare variables needed for I/O
  char buf[BUFSIZE];
  char sendBuf[BUFSIZE];
  char outBuf[(BUFSIZE * 2) + 1];

  memset(buf, 0, BUFSIZE);
  memset(sendBuf, 0, BUFSIZE);
  memset(outBuf, 0, (BUFSIZE*2) + 1);
  
  char lf[1] = {0x0A};

  int pipefromparent[2];
  int pipetoparent[2];
  
  // open the pipes between parent and child                                                                                                                                                                                             
  createPipe(pipefromparent);
  createPipe(pipetoparent);

  // fork the child process and handle
  pid_t pid = fork();
  forkedShell = 1;
  if (pid == -1) {
    fprintf(stderr, "Fork Error: %s\n\n", strerror(errno));
    exit(1);
  } else if (pid == 0) {
    // close unused ends of pipes
    closeFd(pipefromparent[1]);
    closeFd(pipetoparent[0]);

    // close the stdin and dup to proper thing
    closeFd(STDIN);
    dupFd(pipefromparent[0]);

    // close stdout and stderr and dup
    closeFd(STDOUT);
    dupFd(pipetoparent[1]);
    closeFd(STDERR);
    dupFd(pipetoparent[1]);

    // declare and pass this so no warning
    char *arguments[] = {"/bin/bash", NULL};

    if (execvp(arguments[0], arguments) == -1) {
      fprintf(stderr, "Exec Error: Cannot start '\bin\bash', %s\n\r", strerror(errno));
      exit(1);
    }
  } else {
    // parent process                                                                                                                                                                                                                    
    shellPid = pid;

    // close unused ends of pipes                                                                                                                                                                                                        
    closeFd(pipefromparent[0]);
    closeFd(pipetoparent[1]);

    // setup polling                                                                                                                                                                                                                     
    struct pollfd polldata[2];

    // std in poll                                                                                                                                                                                                                       
    polldata[0].fd = acceptFd;
    polldata[0].events = POLLIN | POLLHUP | POLLERR;
    polldata[0].revents = 0;

    // end of output pipe                                                                                                                                                                                                                
    polldata[1].fd = pipetoparent[0];
    polldata[1].events = POLLIN | POLLHUP | POLLERR;
    polldata[1].revents = 0;

    int pollStatus = 0;

    while (1) {
      int bytesRead;

      // polling                                                                                                                                                                                                                         
      if((pollStatus = poll(polldata, 2, 0)) < 0) {
	// there was a poll error                                                                                                                                                                                                        
	fprintf(stderr, "Poll Error: Unsuccessful poll attempt, %s\n\r", strerror(errno));
	exit(1);
      } else if (pollStatus < 1) {
	// no events detected so just continue                                                                                                                                                                                           
	continue;
      } else {
	// event detected so go to reading/writing                                                                                                                                                                                       
	// process input from client
	if (polldata[0].revents & POLLIN) {
	  // read from client
	  memset(sendBuf, 0, BUFSIZE);
	  if ((bytesRead = read (acceptFd, sendBuf, BUFSIZE)) < 0) {
	    fprintf(stderr, "I/O Error: Unable to read from client, %s\n\r", strerror(errno));
	    exit(1);
	  } else if (bytesRead > 0) {
	    if (compressFlag) {
	      char sentDecompress[BUFSIZE];
	      uLong length = BUFSIZE;
	      memset(sentDecompress, 0, BUFSIZE);
	      inf(sendBuf, &length, sentDecompress, &length);
	      memset(sendBuf, 0, BUFSIZE);
	      strcpy(sendBuf, sentDecompress);
	    }
	    memset(buf, 0, BUFSIZE);
	    strcpy(buf, sendBuf);
	    
	    // processing buffer                                                                                                                                                                                                         
	    for (int i = 0; i < bytesRead; i++) {
	      // checkf for <cr> or <lf>                                                                                                                                                                                                 
	      if (buf[i] == 0x0D || buf[i] == 0x0A) {
		writeBytes(pipefromparent[1], lf, 1);
	      } else if (buf[i] == 0x04) {
		// ^D received
		closeFd(pipefromparent[1]);
		flushBuffer(pipetoparent[0], acceptFd);
		exit(0);
	      } else if (buf[i] == 0x03) {
		// ^C received
		kill(shellPid, SIGINT);
	      } else {
		writeBytes(pipefromparent[1], &buf[i], 1);
	      }
	    }
	    
	  } else {
	    closeFd(pipefromparent[1]);
	    flushBuffer(pipetoparent[0], acceptFd);
	    exit(0);
	  }
	}
      }

      // process output from shell                                                                                                                                                                                                
      if (polldata[1].revents & POLLIN) {
	memset(sendBuf, 0, BUFSIZE);
	if ((bytesRead = read(pipetoparent[0], sendBuf, BUFSIZE)) < 0) {
	  fprintf(stderr, "I/O Error: Unable to read from shell: %s\n\r", strerror(errno));
	  exit(1);
	} else if (bytesRead > 0) {
	  memset(outBuf, 0, (BUFSIZE * 2) + 1);
	  for (int i = 0; i < bytesRead; i++) {
	    if (sendBuf[i] == 0x0A) {
	      outBuf[strlen(outBuf)] = 0x0D;
	      outBuf[strlen(outBuf)] = 0x0A;
	    } else {
	      outBuf[strlen(outBuf)] = sendBuf[i];
	    }
	  }
	} else {
	  closeFd(pipefromparent[1]);
	  flushBuffer(pipetoparent[0], acceptFd);
	  exit(0);
	}
	if (compressFlag) {
	  char sentCompress[(BUFSIZE * 2) + 1];
	  uLong length = (BUFSIZE * 2) + 1;
	  memset(sentCompress, 0, (BUFSIZE * 2) + 1);
	  def(outBuf, length, sentCompress, &length);
	  memset(outBuf, 0, (BUFSIZE * 2) + 1);
	  strcpy(outBuf, sentCompress);
	}
	writeBytes(acceptFd, outBuf, (BUFSIZE * 2) + 1);
      }

      // processing EOF or SIGPIPE from shell
      if (polldata[1].revents & (POLLHUP | POLLERR)) {
	exit(1);
      }

      // processing EOF or SIGPIPE from client
      if (polldata[0].revents & (POLLHUP | POLLERR)) {
	closeFd(pipefromparent[1]);
	flushBuffer(pipetoparent[0], acceptFd);
	exit(0);
      } 
    }
  }
  exit(0);
}
