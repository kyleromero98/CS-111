// NAME: Kyle Romero
// EMAIL: kyleromero98@gmail.com
// ID: 204747283

#include <time.h>
#include <getopt.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int numIterations = 1, opt_yield = 0, lock = 0;
char syncArg = '\0';

pthread_mutex_t mutex;

void add(long long *pointer, long long value) {
  long long sum = *pointer + value;
  if (opt_yield)
    sched_yield();
  *pointer = sum;
}

void* iterator(void* counter) {
  // adding phase
  for (int i = 0; i < numIterations; i++) {
    if (syncArg == 'm') {
      // mutex case
      pthread_mutex_lock(&mutex);
      add((long long*) counter, 1);
      pthread_mutex_unlock(&mutex);
    } else if (syncArg == 's') {
      // spin lock case
      while(__sync_lock_test_and_set(&lock, 1));
      add((long long *) counter, 1);
      __sync_lock_release(&lock);
    } else if (syncArg == 'c') {
      // compare and swap case
      long long previous;
      long long sum;
      do {
	previous = *((long long *) counter);
	sum = previous + 1;
	if (opt_yield)
	  sched_yield();
      } while (__sync_val_compare_and_swap((long long*) counter, previous, sum) != previous);
    } else {
      // default case
      add((long long*)counter, 1);
    }
  }
  // subtracting phase
  for (int i = 0; i < numIterations; i++) {
    if (syncArg == 'm')	{
      // mutex case
      pthread_mutex_lock(&mutex);
      add((long long*) counter, -1);
      pthread_mutex_unlock(&mutex);
    } else if (syncArg == 's') {
      // spin lock case
      while(__sync_lock_test_and_set(&lock, 1));
      add((long long *) counter, -1);
      __sync_lock_release(&lock);
    } else if (syncArg == 'c') {
      // compare and swap case
      long long previous;
      long long sum;
      do {
	previous = *((long long *) counter);
        sum = previous + (-1);
	if (opt_yield)	
          sched_yield();
      }	while (__sync_val_compare_and_swap((long long*) counter, previous, sum) != previous);
    } else {
      // default case
      add((long long*)counter, -1);
    }
  }
  return NULL;
}

int main (int argc, char** argv) {
  int numThreads = 1;
  long long counter = 0;
  
  static struct option longOptions[] =
    {
      {"threads", required_argument, NULL, 't'},
      {"iterations", required_argument, NULL, 'i'},
      {"yield", no_argument, NULL, 'y'},
      {"sync", required_argument, NULL, 's'},
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
    case 't':
      // number of threads option
      numThreads = atoi(optarg);
      break;
    case 'i':
      // number of iterations option
      numIterations = atoi(optarg);
      break;
    case 'y':
      // yielding turned on
      opt_yield = 1;
      break;
    case 's':
      // handling sync option
      if (strlen(optarg) == 1) {
	if (optarg[0] == 'm') {
	  syncArg = 'm';
	} else if (optarg[0] == 's') {
	  syncArg = 's';
	} else if (optarg[0] == 'c') {
	  syncArg = 'c';
	} else {
	  fprintf(stderr, "Option Error: Invalid character for option --sync[m,s,c] specified\n");
	  exit(1);
	}
      } else {
	fprintf(stderr, "Option Error: Incorrect number of characters for option --sync=[m,s,c]\n");
	exit(1);
      }
      break;
    case '?':
      // unrecognized option
      fprintf(stderr, "Unrecognized Option: Valid Options: --threads=[thread number] --iterations=[num of iterations] --yield --sync[m,s,c]\n Proper usage: ./lab2_add --threads=10 --iterations=10 --yield --sync=m\n");
      exit(1);
    default:
      fprintf(stderr, "Option Error: Reached default case for option input with status %d\n", status);
      exit(1);
    }
  }

  if (syncArg == 'm') {
    if (pthread_mutex_init(&mutex, NULL)) {
      fprintf(stderr, "Mutex Error: Failed to init mutex, %s", strerror(errno));
      exit(2);
    }
  }
  
  struct timespec start, end;
  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) < 0) {
    fprintf(stderr, "Clock Error: %s\n", strerror(errno));
    exit(2);
  }

  pthread_t *threads = (pthread_t*) malloc (numThreads * sizeof(pthread_t));
  if (threads == NULL) {
    fprintf(stderr, "Allocation Error: Unable to allocate array for thread IDs\n");
    exit(2);
  }

  for (int i = 0; i < numThreads; i++) {
    if(pthread_create(&threads[i], NULL, iterator, &counter)) {
      fprintf(stderr, "Thread Error: Unable to create thread, %s\n", strerror(errno));
      exit(2);
    }
  }

  for (int i = 0; i < numThreads; i++) {
    if (pthread_join(threads[i], NULL)) {
      fprintf(stderr, "Thread Error: Unable to join thread, %s\n", strerror(errno));
      exit(2);
    }
  }

  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end) < 0) {
    fprintf(stderr, "Clock Error: %s\n", strerror(errno));
    exit(2);
  }

  long totalTime = (1000000000 * (end.tv_sec - start.tv_sec)) + (end.tv_nsec - start.tv_nsec);
  int numOperations = numThreads * numIterations *2;
  
  if (!opt_yield) {
    if (syncArg == 'm')
      fprintf(stdout, "add-m,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
    else if (syncArg == 's')
      fprintf(stdout, "add-s,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
    else if (syncArg == 'c')
      fprintf(stdout, "add-c,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
    else
      fprintf(stdout, "add-none,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
  } else {
    if (syncArg == 'm')
      fprintf(stdout, "add-yield-m,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
    else if (syncArg == 's')
      fprintf(stdout, "add-yield-s,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
    else if (syncArg == 'c')
      fprintf(stdout, "add-yield-c,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
    else
      fprintf(stdout, "add-yield-none,%d,%d,%d,%ld,%ld,%lld\n", numThreads, numIterations, numOperations, totalTime, totalTime / numOperations, counter);
  }
    
  free(threads);
}
