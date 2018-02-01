// NAME: Kyle Romero
// EMAIL: kyleromero98@gmail.com
// ID: 204747283

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <poll.h>
#include <signal.h>
#include <wait.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define BUFSIZE 256

static int shellFlag = 0;
static int debugFlag = 0;
struct termios savedAttributes;
pid_t shellPid;

// saves current terminal attributes to attr
void saveTermAttr (struct termios* attr) {
  if (tcgetattr(STDIN, attr) < 0) {
    fprintf(stderr, "Get Attribute Error on FD %d: %s\n", STDIN, strerror(errno));
    exit (2);
  }
}

// sets the IO attributes to attr
void setTermAttr (struct termios* attr) {
  if (tcsetattr(STDIN, TCSANOW, attr) < 0) {
    fprintf(stderr, "Set Attribute Error on FD %d: %s\n", STDIN, strerror(errno));
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

// restores IO attributes and exits the program
void restoreAndExit () {
  // reset attributes to default                                                                                                                                                                                                        
  setTermAttr(&savedAttributes);
  if (shellFlag) {
    int status, result;
    if ((result = waitpid(shellPid, &status, 0)) == -1) {
      fprintf(stderr, "WaitPid Error: Failure to wait for shell to close, %s\n", strerror(errno));
      exit(1);
    } else if (result == shellPid) {
      fprintf(stderr, "SHELL EXIT SIGNAL=%d STATUS=%d\n", (status & 0x007f), WEXITSTATUS(status));
    }
  }
}

// closes a file descriptor with error checking
void closeFd (int fd) {
  if (close(fd) == -1) {
    fprintf(stderr, "I/O Error: Failure to close file descriptor, %s\n", strerror(errno));
    exit(1);
  }
}

void dupFd (int fd) {
  if (dup(fd) == -1) {
    fprintf(stderr, "I/O Error: Failure to dup file descriptor, %s\n", strerror(errno));
    exit(1);
  }
}

// creates a pipe with error checking
void createPipe(int fds[2]) {
  if (pipe(fds) == -1) {
    fprintf(stderr, "Pipe Error: Failure creating pipe, %s\n", strerror(errno));
    exit(1);
  }
}

// wrapper function for write
void writeBytes (int fd, const void *buf, size_t bytes) {
  if (write(fd, buf, bytes) < 0) {
    fprintf(stderr, "I/O Error: Unable to write %s, %s", (char*)buf, strerror(errno));
    exit(1);
  } 
}

// simple sig handler for sigpipe
void signalHandler(int sigNum) {
  if (sigNum == SIGPIPE) {
    fprintf(stderr, "SIGPIPE");
    exit(1);
  }
}

int main (int argc, char** argv) {
  int status;

  // option enumeration
  static struct option longOptions[] =
    {
      {"shell", no_argument, &shellFlag, 1},
      {"debug", no_argument, &debugFlag, 1},
      {0, 0, 0, 0}
    };

  int statusIndex = 0;

  // save initial values of terminal attributes
  saveTermAttr(&savedAttributes);
  // set up some additional stuff
  atexit(restoreAndExit);
  // get the copy of initial values that we will change
  switchToNonCanon();
  
  // option parsing
  while (1) {
    status = getopt_long(argc, argv, "", longOptions, &statusIndex);

    if (status == -1)
      break;

    switch (status) {
      case 0:
	// do nothing because we already set flags
	break;
      case '?':
	fprintf(stderr, "Option Error: Invalid option found. Valid options: --shell\nCorrect usage: ./lab1a --shell\n");
        exit(1);
        break;
      default:
        fprintf(stderr, "Error: Reached default case for options with status %d\n", status);
        exit(1);
    }
  }
  // finish option parsing
  
  // declare our buffer and a constant
  char buf[BUFSIZE];
  char crlf[2] = {0x0D, 0x0A};
  char lf[1] = {0x0A};

  int pipefromparent[2];
  int pipetoparent[2];
  
  if (!shellFlag) {
    while (1) {
      int bytesRead;

      if ((bytesRead = read (STDIN, buf, BUFSIZE)) < 0) {
        fprintf(stderr, "I/O Error: Unable to read from FD %d: %s\n", STDIN, strerror(errno));
        exit(1);
      } else if (bytesRead > 0) {
        // detect if last byte read is C-d
        if (buf[bytesRead - 1] == 0x04) {
          exit(0);
        } else {
	  // checking for <cr> or <lf>
	  for (int i = 0; i < bytesRead; i++) {
	    if (buf[i] == 0x0D || buf[i] == 0x0A)
	      writeBytes(STDOUT, crlf, 2);
	    else
	      writeBytes(STDOUT, &buf[i], 1);
	  }
        }
      }
    }
  } else {
    // register signalHandler
    signal(SIGINT, signalHandler);
    signal(SIGPIPE, signalHandler);
    
    // open the pipes between parent and child
    createPipe(pipefromparent);
    createPipe(pipetoparent);
    
    // fork the child process and handle
    pid_t pid = fork();
    if (pid == -1) {
      fprintf(stderr, "Fork Error: %s\n", strerror(errno));
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
	fprintf(stderr, "Exec Error: Cannot start '\bin\bash', %s\n", strerror(errno));
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
      polldata[0].fd = STDIN;
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
	  fprintf(stderr, "Poll Error: Unsuccessful poll attempt, %s\n", strerror(errno));
	  exit(1);
	} else if (pollStatus < 1) {
	  // no events detected so just continue
	  continue;
	} else {
	  // event detected so go to reading/writing
	  
	  // process input from keyboard
	  if (polldata[0].revents & POLLIN) {
	    // read from std in
	    if ((bytesRead = read (STDIN, buf, BUFSIZE)) < 0) {
	      fprintf(stderr, "I/O Error: Unable to read from FD %d: %s\n", STDIN, strerror(errno));
	      exit(1);
	    } else if (bytesRead > 0) {
	      // processing buffer
	      for (int i = 0; i < bytesRead; i++) {
		if (debugFlag)
		  fprintf(stderr, "Reached the beginning of reading from the input of keyboard\n");

		// checkf for <cr> or <lf>
		if (buf[i] == 0x0D || buf[i] == 0x0A) {
		  writeBytes(STDOUT, crlf, 2);
		  writeBytes(pipefromparent[1], lf, 1);
		} else if (buf[i] == 0x04) {
		  fprintf(stderr, "^D\n");
		  closeFd(pipefromparent[1]);
		  while ((bytesRead = read(pipetoparent[0], buf, BUFSIZE)) > 0) {
		    for (int i = 0; i < bytesRead; i++) {
		      if (buf[i] == 0x0A) {
			writeBytes(STDOUT, crlf, 2);
		      } else {
			writeBytes(STDOUT, &buf[i], 1);
		      }
		    }
		  }
		  if (bytesRead < 0) {
		    fprintf(stderr, "I/O Error: Unable to read from FD %d: %s\n", STDIN, strerror(errno));
		    exit(1);
		  }
		  exit(0);
		} else if (buf[i] == 0x03) {
		  fprintf(stderr, "^C\n");
		  kill(shellPid, SIGINT);		  
		} else {
		  writeBytes(STDOUT, &buf[i], 1);
		  writeBytes(pipefromparent[1], &buf[i], 1);
		}
	      }
	    }
	  }
	}
	  
	// process output from shell
	if (polldata[1].revents & POLLIN) {
	  if ((bytesRead = read(pipetoparent[0], buf, BUFSIZE)) < 0) {
	    fprintf(stderr, "I/O Error: Unable to read from FD %d: %s\n", STDIN, strerror(errno));
	    exit(1);
	  } else if (bytesRead > 0) {
	    if (debugFlag)
	      fprintf(stderr, "Reached the beginning of reading from the output of shell\n");
	  
	    for (int i = 0; i < bytesRead; i++) {
	      if (buf[i] == 0x0A) {
		writeBytes(STDOUT, crlf, 2);
	      } else {
		writeBytes(STDOUT, &buf[i], 1);
	      }
	    }
	  }
	}

	// processing errors
	if (polldata[0].revents & (POLLHUP | POLLERR) || polldata[1].revents & (POLLHUP | POLLERR)) {
	  exit(1);
	}
      }
    }
  }
  exit (0);
}
