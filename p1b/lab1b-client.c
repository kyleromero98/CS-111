// NAME: Kyle Romero
// EMAIL: kyleromero98@gmail.com
// ID: 204747283

// includes
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
#include <fcntl.h>
#include <zlib.h>

// defined constants
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define BUFSIZE 256

// global flags
static int portFlag = 0;
static int debugFlag = 0;
static int compressFlag = 0;
static int terminalFlag = 0;

// global variables
struct termios savedAttributes;

// saves current terminal attributes to attr
void saveTermAttr (struct termios* attr) {
  if (tcgetattr(STDIN, attr) < 0) {
    fprintf(stderr, "Get Attribute Error on FD %d: %s\n\r", STDIN, strerror(errno));
    exit (2);
  }
}

// sets the IO attributes to attr
void setTermAttr (struct termios* attr) {
  if (tcsetattr(STDIN, TCSANOW, attr) < 0) {
    fprintf(stderr, "Set Attribute Error on FD %d: %s\n\r", STDIN, strerror(errno));
    exit (2);
  }
}

// switches our terminal to non canonical input
void switchToNonCanon () {
  struct termios attr;
  saveTermAttr(&attr);
  attr.c_iflag = ISTRIP;
  attr.c_oflag = 0;
  attr.c_lflag = 0;
  setTermAttr(&attr);
}

// called on exit; restores IO attributes
void restoreAndExit () {
  // reset attributes to default
  if (terminalFlag) {
    setTermAttr(&savedAttributes);
  }
}

// wrapper function for write
void writeBytes (int fd, const void *buf, size_t bytes) {
  if (write(fd, buf, bytes) < 0) {
    fprintf(stderr, "I/O Error: Unable to write %s, %s", (char*)buf, strerror(errno));
    exit(1);
  }
}

// compresses src into dest
void def (char* src, unsigned long int src_len, char* dest, uLong* dest_len) {
  // set up
  z_stream defstream;
  defstream.zalloc = Z_NULL;
  defstream.zfree = Z_NULL;
  defstream.opaque = Z_NULL;

  // sets up the stream values
  defstream.avail_in = (uInt) src_len;
  defstream.next_in = (Bytef *) src;
  defstream.avail_out = (uInt) *dest_len;
  defstream.next_out = (Bytef *) dest;

  // does deflating
  deflateInit(&defstream, Z_BEST_COMPRESSION);
  deflate(&defstream, Z_FINISH);
  deflateEnd(&defstream);

  *dest_len = (uInt) ((char*) defstream.next_out - dest);

  // debug output
  if (debugFlag) {
    fprintf(stderr, "Deflated strlen: %lu\n\r", strlen(dest));
    fprintf(stderr, "Deflated: %s\n\r", dest);
    fprintf(stderr, "Deflated Size: %lu\n\r", *dest_len);
  }
}

// decompresses src into dest
void inf (char* src, uLong* src_len, char* dest, uLong* dest_len) {
  // set up
  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;

  // sets up the stream values
  infstream.avail_in = (uInt)(*src_len);
  infstream.next_in = (Bytef *) src;
  infstream.avail_out = (uInt)(*dest_len);
  infstream.next_out = (Bytef *) dest;

  // does inflating
  inflateInit(&infstream);
  inflate(&infstream, Z_NO_FLUSH);
  inflateEnd(&infstream);

  // debug output
  if (debugFlag) {
    fprintf(stderr, "Inflated strlen is: %lu\n\r", strlen(dest));
    fprintf(stderr, "Inflated string is: %s\n\r", dest);
    fprintf(stderr, "Inflated Size: %lu\n\r", *dest_len);
  }
}

// main functions
int main (int argc, char** argv) {

  // variables for option data
  int portNumber;
  char* logFile = NULL;
  
  // init options
  static struct option longOptions[] =
    {
      {"port", required_argument, NULL, 'p'},
      {"log", required_argument, NULL, 'l'},
      {"compress", no_argument, &compressFlag, 1},
      {"debug", no_argument, &debugFlag, 1},
      {0, 0, 0, 0}
    };

  // checking for options
  int status;
  int statusIndex = 0;
  while (1) {
    status = getopt_long(argc, argv, "", longOptions, &statusIndex);

    // no more options so exit
    if (status == -1)
      break;

    switch (status) {
    case 0:
      // do nothing, enters on no_argument
      break;
    case 'p':
      // port option
      portNumber = atoi(optarg);
      portFlag = 1;
      break;
    case 'l':
      // log option
      logFile = optarg;
      break;
    case '?':
      // unrecognized option
      fprintf(stderr, "Unrecognized Option: Valid Options: --port=[port number] --log\n\r Proper usage: ./lab1b-client --port=1234 --log\n\r");
      exit(1);
    default:
      fprintf(stderr, "Option Error: Reached default case for option input with status %d\n\r", status);
      exit(1);
    }
  }

  // check to make sure we got a port
  if (!portFlag) {
    fprintf(stderr, "Option Error: Expected --port=[port number] option\n\r Usage: ./lab1b-client --port=1234\n\r");
    exit(1);
  }

  // init buffer stuff
  char buf[BUFSIZE];
  char sendBuf[BUFSIZE];
  char receiveBuf[(BUFSIZE*2) + 1];
 
  memset(buf, 0, BUFSIZE);
  memset(sendBuf, 0, BUFSIZE);
  memset(receiveBuf, 0, (BUFSIZE*2) + 1);

  // char constant
  char crlf[2] = {0x0D, 0x0A};

  // socket setup
  struct sockaddr_in client;
  int socketFd = 0;
  if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "Network Error: Could not create socket, %s\n\r", strerror(errno));
    exit(1);
  }

  client.sin_addr.s_addr = inet_addr("127.0.0.1");
  client.sin_family = AF_INET;
  client.sin_port = htons(portNumber);

  if (connect(socketFd, (struct sockaddr *) &client, sizeof(client)) < 0) {
    fprintf(stderr, "Network Error: Could not connect socket to server, %s\n\r", strerror(errno));
    exit(1);
  }

  int logFd;
  // setup log file
  if (logFile != NULL) {
    if ((logFd = open(logFile, O_WRONLY | O_CREAT, 00666)) == -1) {
      fprintf(stderr, "I/O Error: Unable to open %s, %s", logFile, strerror(errno));
      exit(1);
    }
  }

  // save the current terminal attr
  saveTermAttr(&savedAttributes);
  // restore these attr on exit
  atexit(restoreAndExit);
  // switch to non canonical input
  switchToNonCanon();
  terminalFlag = 1;
  
  // setup polling                                                                                                                                                                                                                     
  struct pollfd polldata[2];

  // stdin poll                                                                                                                                                                                                             
  polldata[0].fd = STDIN;
  polldata[0].events = POLLIN | POLLHUP | POLLERR;
  polldata[0].revents = 0;

  // socket poll
  polldata[1].fd = socketFd;
  polldata[1].events = POLLIN | POLLHUP | POLLERR;
  polldata[1].revents = 0;
  
  int pollStatus = 0;
  
  while (1) {
    int bytesRead;

    if((pollStatus = poll(polldata, 2, 0)) < 0) {
      // there was a poll error                                                                                                                                                                                                        
      fprintf(stderr, "Poll Error: Unsuccessful poll attempt, %s\n\r", strerror(errno));
      exit(1);
    } else if (pollStatus < 1) {
      // no events detected so just continue                                                                                                                                                                                           
      continue;
    } else {
      // event detected so go to reading/writing
      // process input from keyboard                                                                                                                                                                                                   
      if (polldata[0].revents & POLLIN) {
	if ((bytesRead = read (STDIN, buf, BUFSIZE)) < 0) {
	  fprintf(stderr, "I/O Error: Unable to read from FD %d: %s\n\r", STDIN, strerror(errno));
	  exit(1);
	} else if (bytesRead > 0) {
	  // checking for <cr> or <lf>
	  for (int i = 0; i < bytesRead; i++) {
	    if (buf[i] == 0x0D || buf[i] == 0x0A) {
	      writeBytes(STDOUT, crlf, 2);
	      sendBuf[strlen(sendBuf)] = buf[i];
	      // compression specified
	      if (compressFlag) {
		char sendCompress[BUFSIZE];
		uLong length = BUFSIZE;
		memset(sendCompress, 0, BUFSIZE);
		def(sendBuf, BUFSIZE, sendCompress, &length);
		strcpy(sendBuf, sendCompress);
	      }
	      // send to socket
	      writeBytes(socketFd, sendBuf, strlen(sendBuf));
	      
	      if (debugFlag) {
		fprintf(stderr, "SENT %d bytes: %s\n\r", (int)strlen(sendBuf), sendBuf);
	      }
	      
	      if (logFile != NULL) {
		dprintf(logFd, "SENT %d bytes: %s\n", (int)strlen(sendBuf), sendBuf);
	      }	      
	      memset(sendBuf, 0, BUFSIZE);
	    } else {
	      writeBytes(STDOUT, &buf[i], 1);
	      sendBuf[strlen(sendBuf)] = buf[i];
	    }
	  }
	} else {
	  exit(0);
	}
      }

      if (polldata[1].revents & POLLIN) {
	if ((bytesRead = read(socketFd, receiveBuf, (BUFSIZE*2) + 1)) < 0) {
	  fprintf(stderr, "I/O Error: Unable to read from FD %d: %s\n\r", socketFd, strerror(errno));
	  exit(1);
	} else if (bytesRead > 0) {
	  // checking more than one character read
	  char outputBuf[(BUFSIZE * 2) + 1];
	  char decompressed[(BUFSIZE*2) + 1];
	  memset(outputBuf, 0, (BUFSIZE * 2) + 1);

	  if (logFile != NULL) {
            dprintf(logFd, "RECEIVED %d bytes: %s\n", (int)strlen(receiveBuf), receiveBuf);
          }
	  
	  if (compressFlag) {
	    uLong length = (BUFSIZE * 2) + 1;
	    memset(decompressed, 0, (BUFSIZE * 2) + 1);
	    inf(receiveBuf, &length, decompressed, &length);
	    strcpy(outputBuf, decompressed);
	  } else {
	    strcpy(outputBuf, receiveBuf);
	  }
	  writeBytes(STDOUT, outputBuf, strlen(outputBuf));
	  memset(receiveBuf, 0, (BUFSIZE*2)+1);

	  if (debugFlag) {
	    fprintf(stderr, "RECEIVED %d bytes: %s\n\r", (int)strlen(outputBuf), outputBuf);
	  }
	} else {
	  exit(0);
	}
      }
    }
    //error checking
    if (polldata[0].revents & (POLLHUP | POLLERR)) {
      exit(1);
    }
  }

  if (logFile != NULL) {
    if (close(logFd) == -1) {
      fprintf(stderr, "I/O Error: Unable to close file %s, %s\n\r", logFile, strerror(errno));
      exit(1);
    }
  }
  exit(0);
}
