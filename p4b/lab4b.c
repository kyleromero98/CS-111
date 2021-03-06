// NAME:Kyle Romero
// EMAIL:kyleromero98@gmail.com
// ID:204747283

#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <mraa.h>
#include <mraa/aio.h>
#include <mraa/gpio.h>
#include <math.h>
#include <poll.h>

#define STDIN 0
#define BUFSIZE 256

// flags
sig_atomic_t volatile sampleFlag = 1;
int isStopped = 0;

// constants
const int B = 4275;
const int R0 = 100000;

// constants fro timestamp
time_t raw_time;
struct tm* current_time;

// allows easy exiting
mraa_gpio_context button;
mraa_aio_context tempSensor;
int logFd = -1;

// Input options
enum opt_index {
  SCALE = 0,
  PERIOD = 1,
  STOP = 2,
  START = 3,
  LOG = 4,
    OFF = 5
};

// names of valid options
char* opt_name[6] = {
  "SCALE",
  "PERIOD",
  "STOP",
  "START",
  "LOG",
  "OFF"
};

// prints the current timestamp
void getTimestamp(char *time_str) {
  time(&raw_time);
  current_time = localtime(&raw_time);
  sprintf(time_str, "%02d:%02d:%02d", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
}

// calculates the temperature from analog signal
float analogToTemp(int voltage) {
  float R = 1023.0/voltage-1.0;
  R = R0*R;
  float cel = 1.0/(log(R/R0)/B+1/298.15)-273.15;
  return cel;
}

// exits on button press
void button_press() {
  exit(0);
}

// closes everything, logs and exits
void closeAndExit () {
  mraa_gpio_close(button);
  mraa_aio_close(tempSensor);
  char time[20];
  getTimestamp(time);
  // prints timestamp to stdout
  fprintf(stdout, "%s SHUTDOWN\n", time);
  if (logFd != -1) {
    // closes and logs file if logging is enabled
    dprintf(logFd, "%s SHUTDOWN\n", time);
    if (close(logFd) == -1) {
      fprintf(stderr, "I/O Error: Unable to close logfile, %s\n\r", strerror(errno));
      exit(1);
    }
  }
}

int main (int argc, char **argv) {

  // vars for input options
  long sample_period = 1000000;
  char scale = 'F';
  char *logFile = NULL;
  
  // possible command line options
  static struct option longOptions[] =
    {
      {"period", required_argument, 0, 'p'},
      {"scale", required_argument, 0, 's'},
      {"log", required_argument, 0, 'l'},
      {0, 0, 0, 0}
    };

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
      // length of sampling interval in seconds
      sample_period = (float) (sample_period * strtod(optarg, NULL));
      break;
    case 's':
      // the scale of temperature reading
      if (strlen(optarg) == 1 && optarg[0] == 'C')
	scale = 'C';
      else if (strlen(optarg) == 1 && optarg[0] == 'F')
	scale = 'F';
      else {
	fprintf(stderr, "Option Error: Invalid selection for option --scale=[F(default),C]");
	exit(1);
      }
      break;
    case 'l':
      // handles the logfile
      logFile = optarg;
      break;
    case '?':
      // unrecognized option
      fprintf(stderr, "Unrecognized Option: Valid Options: --period=[sample interval in seconds (default=1)] --scale=[F(default),C] --log=[filename]\n Proper usage: ./lab4b --period=2 --scale=C --log=log.txt\n");
      exit(1);
    default:
      fprintf(stderr, "Option Error: Reached default case for option input with status %d\n", status);
      exit(1);
    }
  }

  // set up the button and sensor
  button = mraa_gpio_init(62);
  tempSensor = mraa_aio_init(1);

  atexit(closeAndExit);
  
  mraa_gpio_dir(button, MRAA_GPIO_IN);

  mraa_gpio_isr(button, MRAA_GPIO_EDGE_RISING, &button_press, NULL);

  int reading = 0;

  // setup log file
  if (logFile != NULL) {
    if ((logFd = open(logFile, O_WRONLY | O_CREAT | O_TRUNC, 00666)) == -1) {
      fprintf(stderr, "I/O Error: Unable to open %s, %s", logFile, strerror(errno));
      exit(1);
    }
  }

  // setup polling
  struct pollfd polldata[1];

  // stdin poll
  polldata[0].fd = STDIN;
  polldata[0].events = POLLIN | POLLHUP | POLLERR;
  polldata[0].revents = 0;

  int pollStatus = 0;

  int bytesRead = 0;
  int cmdbufOffset = 0;
  char buf[BUFSIZE];
  char cmdbuf[BUFSIZE];

  // init buffers
  memset(buf, 0, BUFSIZE);
  memset(cmdbuf, 0, BUFSIZE);
  
  while (sampleFlag) {
    // sampling happens here
    if (!isStopped) {
      reading = mraa_aio_read(tempSensor);
    
      float temp = analogToTemp(reading);
      if (scale == 'F')
	temp = (temp * 9 / 5) + 32;
    
      char time[20];
      getTimestamp(time);
    
      fprintf(stdout, "%s %.1f\n", time, temp);
    
      if (logFile != NULL) {
	dprintf(logFd, "%s %.1f\n", time, temp);
      }
    }

    // sleep for the specified period
    usleep(sample_period);
    
    if((pollStatus = poll(polldata, 2, 0)) < 0) {
      // there was a poll error
      fprintf(stderr, "Poll Error: Unsuccessful poll attempt, %s\n\r", strerror(errno));
      exit(1);
    } else if (pollStatus < 1) {
      // no events detected so just continue
      continue;
    } else {
      // process input from keyboard
      if (polldata[0].revents & POLLIN) {
	if ((bytesRead = read (STDIN, buf, BUFSIZE)) < 0) {
	  fprintf(stderr, "I/O Error: Unable to read from FD %d: %s\n\r", STDIN, strerror(errno));
	  exit(1);
	} else if (bytesRead > 0) {
	  memcpy(&cmdbuf[cmdbufOffset], &buf, bytesRead);
	  cmdbufOffset += bytesRead;
	  int i = 0;
	  for (i = 0; i < cmdbufOffset && cmdbufOffset != 0; i++) {
	    if (cmdbuf[i] == '\n') {
	      // log the command to file
	      if (logFile != NULL) {
		int a = 0;
		for (a = 0; a < i; a++) {
		  dprintf(logFd, "%c", cmdbuf[a]);
		}
		dprintf(logFd, "\n");
	      }

	      cmdbuf[i] = 0;
	      char *opt = NULL;
	      size_t optLen = 0;

	      // process the command
	      if (strcmp(cmdbuf, opt_name[STOP]) == 0) {
		isStopped = 1;
	      } else if (strcmp(cmdbuf, opt_name[START]) == 0) {
		isStopped = 0;
	      } else if (strcmp(cmdbuf, opt_name[OFF]) == 0) {
		exit(0);
	      } else {
		ssize_t offset = 0;
		
		// search until the equals sign for option params
		for (offset = 0; offset < i; offset++) {
		  if (cmdbuf[offset] == '=') {
		    cmdbuf[offset] = 0;
		    // get size of option passed
		    optLen = strlen(cmdbuf + offset + 1) + 1;
		    opt = (char*) malloc(sizeof(char) * optLen);
		    strcpy(opt, cmdbuf + offset + 1);
		    // opt now holds all of the option
		    if (strcmp(cmdbuf, opt_name[LOG]) == 0) {
		      // logs the option to file
		      if (logFile != NULL) {
			dprintf(logFd, "%s\n", opt);
		      }
		      break;
		    } else if (strcmp(cmdbuf, opt_name[SCALE]) == 0) {
		      // updates the scale if needed
		      if (strlen(opt) != 1 && !(opt[0] == 'F' || opt[0] == 'C')) {
			break;
		      }
		      scale = opt[0];
		      break;
		    } else if (strcmp(cmdbuf, opt_name[PERIOD]) == 0) {
		      // updates the period if needed
		      double newPeriod = strtod(opt, NULL);
		      if (newPeriod < 0) {
			break;
		      }
		      sample_period = (float) (newPeriod * 1e6);
		      break;
		    }
		  }
		}
	      }

	      // shift down the buffer
	      memcpy(cmdbuf, &cmdbuf[i+1], BUFSIZE - i - 1);
	      cmdbufOffset = cmdbufOffset - i - 1;
	      i = 0;
	    }
	  }
	}
      }
    }
  }
  exit(0);
}
