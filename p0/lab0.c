// NAME: Kyle Romero
// EMAIL: kyleromero98@gmail.com
// ID: 204747283

#include <getopt.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// flags for options
static int segfault_flag = 0;
static int catch_flag = 0;

// subroutines for throwing and handling SIGSEGV
void sighandler();
void throw_seg();

int main (int argc, char** argv) {
  int status;

  char* input_file = NULL;
  char* output_file = NULL;

  while (1) {
    // initialize options
    static struct option long_options[] =
      {
	{"input", required_argument, NULL, 'a'},
	{"output", required_argument, NULL, 'b'},
	{"segfault", no_argument, &segfault_flag, 1},
	{"catch", no_argument, &catch_flag, 1},
	{0, 0, 0, 0}
      };

    int status_index = 0;
    
    // get the command line options and set flags
    status = getopt_long(argc, argv, "", long_options, &status_index);

    if (status == -1)
      break;

    switch (status) {
      case 0:
	// do nothing because flags already set
	break;
      case 'a':
	input_file = optarg;
	break;
      case 'b':
	output_file = optarg;
	break;
      case '?':
	fprintf(stderr, "Option Error: Invalid option found. Valid options: --input= --output= --segfault --catch\n Correct usage: ./lab0 --segfault --catch --input=input.txt --output=output.txt\n");
	exit(1);
	break;
      default:
	fprintf(stderr, "Error: Reached default case for options with status %d\n", status);
	abort();
    }
  }

  // loading input and output sources
  // file redirection of input source
  if (input_file != NULL) {
    int inputsource = 0;
    if ((inputsource = open(input_file, O_RDONLY)) < 0) {
      fprintf(stderr, "IO Error: Unable to open %s for --input: %s\n", input_file, strerror(errno));
      exit(2);
    }

    if (close(0) < 0) {
      fprintf(stderr, "IO Error: Error closing STDIN for --input redirection: %s\n", strerror(errno));
      exit(5);
    }
    
    if (dup(inputsource) < 0) {
      fprintf(stderr, "IO Error: Error duplicating %s to FD 0 for --input redirection: %s\n", input_file, strerror(errno));
      exit(5);
    }
  }

  // file redirection of output source
  if (output_file != NULL) {
    int outputsource = 1;
    if ((outputsource = open(output_file, O_WRONLY | O_CREAT, 00666)) < 0) {
      fprintf(stderr, "IO Error: Unable to open %s for --output: %s\n", output_file, strerror(errno));
      exit(3);
    }

    if (close(1) < 0) {
      fprintf(stderr, "IO Error: Error closing STDOUT for --output redirection: %s\n", strerror(errno));
      exit(5);
    }

    if (dup(outputsource) < 0) {
      fprintf(stderr, "IO Error: Error duplicating %s to FD 1 for --output redirection: %s\n", input_file, strerror(errno));
      exit(5);
    }
  }

  // register the signal handler
  if (catch_flag)
    signal(SIGSEGV, sighandler);

  // cause the segfault
  if (segfault_flag)
    throw_seg();

  // continue on to copying from input to output
  char currentchar;
  int stat = 0;
  while ((stat = read(0, &currentchar, 1)) == 1) {
    if (stat < 0) {
      fprintf(stderr, "IO Error: Error reading from file %s: %s\n", input_file, strerror(errno));
      exit(5);
    }
    if (write(1, &currentchar, 1) < 0) {
      fprintf(stderr, "IO Error: Error writing to file %s: %s\n", output_file, strerror(errno));
    }
  }

  // close our streams
  if (close(0) < 0) {
    fprintf(stderr, "IO Error: Unable to close %s as input file: %s\n", input_file, strerror(errno));
    exit(5);
  }

  if (close(1) < 0) {
    fprintf(stderr, "IO Error: Unable to close %s as output file: %s\n", output_file, strerror(errno));
    exit(5);
  }

  // exit successfully
  exit(0);
}

void sighandler () {
  fprintf(stderr, "SIGSEGV Error: Successful --catch option\n");
  exit(4);
}

void throw_seg() {
  // this is how the spec said to do this
  char* temp = NULL;
  *temp = 'k';
}
