// NAME:Kyle Romero
// EMAIL:kyleromero98@gmail.com
// ID:204747283

#include <netdb.h>
#include <ctype.h>
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
#include <math.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

// includes for SSL
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#define STDIN 0
#define BUFSIZE 256

// flags
sig_atomic_t volatile sampleFlag = 1;
int isStopped = 0;
int idFlag = 0;
int hostFlag = 0;
int logFlag = 0;
int portFlag = 0;
int debugFlag = 0;

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

// closes everything, logs and exits
void closeAndExit () {
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

// finds the ip address from the hostname
int hostToIP(char *hostname , char *ip) {
  int i;
  struct hostent *hoste;
  struct in_addr **address_list;
  
  if ((hoste = gethostbyname(hostname)) == NULL)
    {
      // failure detected
      fprintf(stderr, "Network Error: Hostname could not be resolved to IP\n");
      exit(1);
      return 1;
    }

  address_list = (struct in_addr **) hoste->h_addr_list;
  for(i = 0; address_list[i] != NULL; i++) {
    //Return the first address that was found
    strcpy(ip , inet_ntoa(*address_list[i]) );
    return 0;
  }
  return 1;
}

int main (int argc, char **argv) {

  // vars for input options
  long sample_period = 1000000;
  char scale = 'F';
  char *logFile = NULL;
  char *idNumber = NULL;
  char *hostName = NULL;
  int portNumber = 0;
  
  // possible command line options
  static struct option longOptions[] =
    {
      {"period", required_argument, 0, 'p'},
      {"scale", required_argument, 0, 's'},
      {"log", required_argument, 0, 'l'},
      {"id", required_argument, 0, 'i'},
      {"host", required_argument, 0, 'h'},
      {"log", required_argument, 0, 'l'},
      {"debug", no_argument, 0, 'd'},
      {0, 0, 0, 0}
    };

  int status;
  int statusIndex = 0;
  while (1) {
    status = getopt_long(argc, argv, "", longOptions, &statusIndex);
    
    // no more options so exit
    if (status == -1) {
      // have exactly one remaining argument
      if (argc == (optind + 1)) {
	portFlag = 1;
	// check for only digits in port number
	int i = 0;
	while (argv[optind][i] != '\0') {
	  if (!isdigit(argv[optind][i])) {
	    fprintf(stderr, "Option Error: Port number contains non-digit characters\n");
	    exit(1);
	  }
	  i++;
	}
	portNumber = atoi(argv[optind]);
      }
      if ((idFlag & hostFlag & logFlag & portFlag) != 1) {
	fprintf(stderr, "Option Error: All required arguments, port, host, log, and id were not specified\n");
	exit(1);
      }
      break;
    }

    switch (status) {
    case 0:
      // do nothing, enters on no_argument
      fprintf(stderr, "%s\n", optarg);
      fprintf(stderr, "0 case\n");
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
      logFlag = 1;
      break;
    case 'i':
      // checking to be sure the passed ID is 9 characters
      if (strlen(optarg) != 9) {
	fprintf(stderr, "Option Error: %s has invalid length for ID number, should be 9\n", optarg);
	exit(1);
      }
      // checking if all digits
      int i = 0;
      while (optarg[i] != '\0') {
	if (!isdigit(optarg[i])) {
	  fprintf(stderr, "Option Error: %s should only contain digits\n", optarg);
	  exit(1);
	}
	i++;
      }
      idNumber = optarg;
      idFlag = 1;
      break;
    case 'h':
      // handles hostname
      hostFlag = 1;
      hostName = optarg;
      break;
    case 'd':
      debugFlag = 1;
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

  // set up the sensor
  tempSensor = mraa_aio_init(1);

  atexit(closeAndExit);

  if (debugFlag)
    fprintf(stderr, "Opening socket...\n");
  // socket setup
  struct sockaddr_in client;
  int socketFd = 0;
  if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "Network Error: Could not create socket, %s\n\r", strerror(errno));
    exit(2);
  }

  if (debugFlag)
    fprintf(stderr, "Socket opened\n");

  char ipaddress[100];
  strcpy(ipaddress, hostName);
  if (!isdigit(ipaddress[0])) {
    hostToIP(hostName, ipaddress);
  }

  client.sin_addr.s_addr = inet_addr(ipaddress);
  if (client.sin_addr.s_addr == INADDR_NONE) {
    fprintf(stderr, "Network Error: INvalid hostname\n");
    exit(1);
  }
  
  client.sin_family = AF_INET;
  client.sin_port = htons(portNumber);

  if (debugFlag)
    fprintf(stderr, "Establishing connection to %s:%d...\n", hostName, portNumber);
  
  if (connect(socketFd, (struct sockaddr *) &client, sizeof(client)) < 0) {
    fprintf(stderr, "Network Error: Could not connect socket to server, %s\n\r", strerror(errno));
    exit(2);
  }

  if (debugFlag)
    fprintf(stderr, "Connection established\n");
  
  int reading = 0;
  
  // setup log file
  if ((logFd = open(logFile, O_WRONLY | O_CREAT | O_TRUNC, 00666)) == -1) {
    fprintf(stderr, "I/O Error: Unable to open %s, %s", logFile, strerror(errno));
    exit(2);
  }

  SSL* ssl_descriptor;
  // open SSL connection
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();

  const SSL_METHOD* ssl_conn = SSLv23_client_method();

  SSL_CTX* ssl_fw = SSL_CTX_new(ssl_conn);
  if (ssl_fw == NULL) {
    fprintf(stderr, "SSL Error: Creating new SSL_CTX_new failed\n");
    exit(2);
  }

  ssl_descriptor = SSL_new(ssl_fw);
  if (ssl_descriptor == NULL) {
    fprintf(stderr, "SSL Error: Creating SSL_new failed\n");
    exit(2);
  }

  if (SSL_set_fd(ssl_descriptor, socketFd) == 0) {
    fprintf(stderr, "SSL Error: Call to SSL_set_fd failed\n");
    exit(2);
  }

  if (SSL_connect(ssl_descriptor) < 1) {
    fprintf(stderr, "SSL Error: Failed to establish SSL connection\n");
    exit(2);
  }
  // end of getting ssl to connect
  
  char buf[BUFSIZE];
  // log ID number
  dprintf(logFd, "ID=%s\n", idNumber);
  snprintf(buf, BUFSIZE, "ID=%s\n", idNumber);
  if (SSL_write(ssl_descriptor, buf, strlen(buf)) < 0) {
    fprintf(stderr, "I/O Error: Failed to write to netwrok socket, %s", strerror(errno));
    exit(2);
  }

  if (debugFlag)
    fprintf(stderr, "Polling...\n");
  
  // setup polling
  struct pollfd polldata[1];

  // stdin poll
  polldata[0].fd = socketFd;
  polldata[0].events = POLLIN | POLLHUP | POLLERR;
  polldata[0].revents = 0;

  int pollStatus = 0;

  int bytesRead = 0;
  int cmdbufOffset = 0;
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

      // write to socket and log
      snprintf(buf, BUFSIZE, "%s %.1f\n", time, temp);
      if (SSL_write(ssl_descriptor, buf, strlen(buf)) < 0) {
	fprintf(stderr, "I/O Error: Failed to write to netwrok socket, %s", strerror(errno));
	exit(2);
      }
      dprintf(logFd, "%s %.1f\n", time, temp);
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
	if ((bytesRead = SSL_read(ssl_descriptor, buf, BUFSIZE)) < 0) {
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
		      dprintf(logFd, "%s\n", opt);
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
