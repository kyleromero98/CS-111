// NAME: Kyle Romero
// EMAIL: kyleromero98@gmail.com
// ID: 204747283

#include "SortedList.h"
#include <time.h>
#include <getopt.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

#define KEYLEN 15
#define NUMLETTERS 26

long long totalIterations = 0;
int numIterations = 1, numThreads = 1, numLists = 1, opt_yield = 0, yieldModeLength = 0, totalLength = 0;
char syncArg = '\0';
char yieldMode[4] = "\0\0\0\0";

pthread_mutex_t *mutexes;
int *spinlocks;
SortedList_t *lists;

SortedListElement_t *initElems;

long long *waitTimes = NULL;

void handleYieldModes(char* options) {
  for (int i = 0; options[i] != '\0'; i++) {
    if (options[i] == 'i') {
      opt_yield |= INSERT_YIELD;
      yieldMode[yieldModeLength++] = 'i';
    } else if (options[i] == 'd') {
      opt_yield |= DELETE_YIELD;
      yieldMode[yieldModeLength++] = 'd';
    } else if (options[i] == 'l') {
      opt_yield |= LOOKUP_YIELD;
      yieldMode[yieldModeLength++] = 'l';
    } else {
      fprintf(stderr, "Option Error: Invalid argument for option --yield=[idl]");
      exit(1);
    }
  }
}

// hash function from stack overflow
// https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    for (int i = 0; i < KEYLEN; i++)
        hash = ((hash << 5) + hash) + str[i];
    return hash;
}

void initElements() {
  srand(time(0));
  for (int i = 0; i < totalIterations; i++) {
    int length = (rand() % KEYLEN) + 5;
    int letter = (rand() % NUMLETTERS);
    char *randomKey = malloc(sizeof(char) * (length + 1));
    for (int a = 0; a < length; a++) {
      randomKey[a] = 'a' + letter;
      letter = rand() % NUMLETTERS;
    }
    randomKey[length] = '\0';
    initElems[i].key = randomKey;
  }
}

long long timeDiff (struct timespec* start, struct timespec* end) {
  long long elapsed = (end->tv_sec - start->tv_sec) * 1000000000;
  elapsed += (end->tv_nsec - start->tv_nsec); 
  return elapsed;
}

void* manipulateThreads (void *threadId) {
  struct timespec start, end;
  int tid = (*(int*)threadId);
  SortedList_t *currList = NULL;

  // insert into list
  for (int i = tid; i < totalIterations; i += numThreads) {
    int listId = hash(initElems[i].key) % numLists;
    currList = &lists[listId];
    switch(syncArg) {
    case 'm':
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
      pthread_mutex_lock(&mutexes[listId]);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
      waitTimes[tid] += timeDiff(&start, &end);
      
      SortedList_insert(currList, &initElems[i]);
      pthread_mutex_unlock(&mutexes[listId]);
      break;
    case 's':
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
      while(__sync_lock_test_and_set(&spinlocks[listId], 1));
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
      waitTimes[tid] +=	timeDiff(&start, &end);
      
      SortedList_insert(currList, &initElems[i]);
      __sync_lock_release(&spinlocks[listId]);
      break;
    default:
      SortedList_insert(currList, &initElems[i]);
      break;
    }
  }

  int currListLength = 0;
  // get list length
  switch (syncArg) {
  case 'm':
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < numLists; i++)
      pthread_mutex_lock(&mutexes[i]);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    waitTimes[tid] += timeDiff(&start, &end);
    for (int i = 0; i < numLists; i++) {
      currListLength = SortedList_length(&lists[i]);
      if (currListLength < 0) {
	fprintf(stderr, "Corruption Detected: Post-element insertion, call to SortedList_length failed with value %d\n", currListLength);
	exit(2);
      }
      totalLength += currListLength;
    }
    for (int i = 0; i < numLists; i++)
      pthread_mutex_unlock(&mutexes[i]);
    break;
  case 's':
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int i = 0; i < numLists; i++)
      while(__sync_lock_test_and_set(&spinlocks[i], 1));
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    waitTimes[tid] += timeDiff(&start, &end);
    
    for (int i = 0; i < numLists; i++) {
      currListLength = SortedList_length(&lists[i]);
      if (currListLength < 0) {
	fprintf(stderr, "Corruption Detected: Post-element insertion, call to SortedList_length failed with value %d\n", currListLength);
	exit(2);
      }
      totalLength += currListLength;
    }
    for (int i = 0; i < numLists; i++)
      __sync_lock_release(&spinlocks[i]);
    break;
  default:
    for (int i = 0; i < numLists; i++) {
      currListLength = SortedList_length(&lists[i]);
      if (currListLength < 0) {
        fprintf(stderr, "Corruption Detected: Post-element insertion, call to SortedList_length failed with value %d\n", currListLength);
        exit(2);
      }
      totalLength += currListLength;
    }
    break;
  }

  SortedListElement_t *temp;
  int listId = 0;
  for (int i = tid; i < totalIterations; i += numThreads) {
    listId = hash(initElems[i].key) % numLists;
    currList = &lists[listId];
    switch(syncArg) {
    case 'm':
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
      pthread_mutex_lock(&mutexes[listId]);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
      waitTimes[tid] += timeDiff(&start, &end);
    
      temp = SortedList_lookup(currList, initElems[i].key);
      if (temp == NULL) {
	fprintf(stderr, "Corrupt List: Unable to find key that was inserted\n");
	exit(2);
      }
      if (SortedList_delete(temp)) {
	fprintf(stderr, "Corrupt List: delete failed\n");
	exit(2);
      }
      pthread_mutex_unlock(&mutexes[listId]);
      break;
    case 's':
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
      while(__sync_lock_test_and_set(&spinlocks[listId], 1));
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
      waitTimes[tid] += timeDiff(&start, &end);
      
      temp = SortedList_lookup(currList, initElems[i].key);
      if (temp == NULL) {
	fprintf(stderr, "Corrupt List: Unable to find key that was inserted\n");
	exit(2);
      }
      if (SortedList_delete(temp)) {
	fprintf(stderr, "Corrupt List: delete failed\n");
	exit(2);
      }
      __sync_lock_release(&spinlocks[listId]);
      break;
    default:
      temp = SortedList_lookup(currList, initElems[i].key);
      if (temp == NULL) {
	fprintf(stderr, "Corrupt List: Unable to find key that was inserted\n");
	exit(2);
      }
      if (SortedList_delete(temp)) {
	fprintf(stderr, "Corrupt List: delete failed\n");
	exit(2);
      }
      break;
    }
  }
  return NULL;
}

void sighandler() {
  fprintf(stderr, "SIGSEGV Error: Segmentation fault detected\n");
  exit(2);
}

int main (int argc, char** argv) {

  signal(SIGSEGV, sighandler);
  
  static struct option longOptions[] = 
    {
      {"threads", required_argument, 0, 't'},
      {"iterations", required_argument, 0, 'i'},
      {"lists", required_argument, 0, 'l'},
      {"yield", required_argument, 0, 'y'},
      {"sync", required_argument, 0, 's'},
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
      handleYieldModes(optarg);
      break;
    case 's':
      // handling sync option
      if (strlen(optarg) == 1 && optarg[0] == 'm') {
	syncArg = 'm';
      } else if (strlen(optarg) == 1 && optarg[0] == 's') {
	syncArg = 's';
      } else {
	fprintf(stderr, "Option Error: Invalid character for option --sync=[m,s,c] specified\n");
	exit(1);
      }
      break;
    case 'l':
      numLists = atoi(optarg);
      break;
    case '?':
      // unrecognized option
      fprintf(stderr, "Unrecognized Option: Valid Options: --threads=[thread number] --iterations=[num of iterations] --yield=[idl] --sync[ms]\n Proper usage: ./lab2_add --threads=10 --iterations=10 --yield=idl --sync=m\n");
      exit(1);
    default:
      fprintf(stderr, "Option Error: Reached default case for option input with status %d\n", status);
      exit(1);
    }
  }

  // initialize lists based on the number of threads
  lists = malloc(numLists * sizeof(SortedList_t));
  if (lists == NULL) {
    fprintf(stderr, "Allocation Error: Unable to allocate initial lists\n");
    exit(2);
  }

  for (int i = 0; i < numLists; i++) {
    lists[i].key = NULL;
    lists[i].next = &lists[i];
    lists[i].prev = &lists[i];
  }

  // initialize mutexes
  if (syncArg == 'm') {
    mutexes = malloc(numLists * sizeof(pthread_mutex_t));
    if (mutexes == NULL) {
      fprintf(stderr, "Allocation Error: Unable to allocate initial mutexes\n");
      exit(2);
    }
    for (int i = 0; i < numLists; i++) {
      if (pthread_mutex_init(&mutexes[i], NULL)) {
	fprintf(stderr, "Mutex Error: Failed to init a mutex, %s\n", strerror(errno));
	exit(2);
      }
    }
  }

  if (syncArg == 's') {
    spinlocks = malloc (numLists * sizeof(int));
    if (spinlocks == NULL) {
      fprintf(stderr, "Allocation Error: Unable to allocate initial spinlocks\n");
      exit(2);
    }
    memset(spinlocks, 0, numLists * sizeof(int));
  }

  totalIterations = numThreads * numIterations;

  initElems = NULL;
  initElems = malloc(sizeof(SortedListElement_t) * totalIterations);
  if (initElems == NULL) {
    fprintf(stderr, "Allocation Error: Unable to allocate space for initialized elements\n");
    exit(2);
  }

  initElements();
  
  pthread_t *threads = NULL;
  threads = malloc(numThreads * sizeof(pthread_t));
  if (threads == NULL) {
    fprintf(stderr, "Allocation Error: Unable to allocate space for threads\n");
    exit(2);
  }
  memset(threads, 0, numThreads * sizeof(pthread_t));
  
  int *threadIds = NULL;
  threadIds = malloc(numThreads * sizeof(int));
  if (threadIds == NULL) {
    fprintf(stderr, "Allocation Error: Unable to allocate space for thread IDs\n");
    exit(2);
  }
  memset(threadIds, 0, numThreads * sizeof(int));

  if (syncArg != '\0') {
    waitTimes = malloc(numThreads * sizeof(long long));
    if (waitTimes == NULL) {
      fprintf(stderr, "Allocation Error: Unable to allocate space for thread wait times\n");
      exit(2);
    }
    memset(waitTimes, 0, numThreads * sizeof(long long));
  }

  struct timespec start, end;
  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) < 0) {
    fprintf(stderr, "Clock Error: %s\n", strerror(errno));
    exit(2);
  }
  
  for (int i = 0; i < numThreads; i++) {
    threadIds[i] = i;
    if(pthread_create(&threads[i], NULL, manipulateThreads, &threadIds[i])) {
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
  
  int totalLength = 0;
  for (int i = 0; i < numLists; i++) {
    int currentListLength = SortedList_length(&lists[i]);
    if (currentListLength < 0) {
      fprintf(stderr, "Corruption Detected: Post-element insertion, call to SortedList_length failed with value %d\n", currentListLength);
      exit(2);
    }
    totalLength += currentListLength;
  }
  
  if (totalLength != 0) {
    fprintf(stderr, "Corruption Error: List length is not 0 after all threads have completed\n");
    exit(2);
  }
  
  long long totalTime = timeDiff(&start, &end);
  int numOperations = totalIterations * 3;

  long long totalWaitTime = 0;
  if (syncArg != '\0') {
    for (int i = 0; i < numThreads; i++)
      totalWaitTime += waitTimes[i];
  }

  if (strlen(yieldMode) == 0) {
    if (syncArg == '\0') {
      fprintf(stdout, "list-none-none,%d,%d,%d,%d,%lld,%lld,%lld\n", numThreads, numIterations, numLists, numOperations, totalTime, totalTime / numOperations, totalWaitTime / numOperations);
    } else if (syncArg == 's') {
      fprintf(stdout, "list-none-s,%d,%d,%d,%d,%lld,%lld,%lld\n", numThreads, numIterations, numLists, numOperations, totalTime, totalTime / numOperations, totalWaitTime / numOperations);
    } else if (syncArg == 'm') {
      fprintf(stdout, "list-none-m,%d,%d,%d,%d,%lld,%lld,%lld\n", numThreads, numIterations, numLists, numOperations, totalTime, totalTime / numOperations, totalWaitTime / numOperations);
    }
  } else {
    if (syncArg == '\0') {
      fprintf(stdout, "list-%s-none,%d,%d,%d,%d,%lld,%lld,%lld\n", yieldMode, numThreads, numIterations, numLists, numOperations, totalTime, totalTime / numOperations, totalWaitTime / numOperations);
    } else if (syncArg == 's') {
      fprintf(stdout, "list-%s-s,%d,%d,%d,%d,%lld,%lld,%lld\n", yieldMode, numThreads, numIterations, numLists, numOperations, totalTime, totalTime / numOperations, totalWaitTime / numOperations);
    } else if (syncArg == 'm') {
      fprintf(stdout, "list-%s-m,%d,%d,%d,%d,%lld,%lld,%lld\n", yieldMode, numThreads, numIterations, numLists, numOperations, totalTime, totalTime / numOperations, totalWaitTime / ((numIterations * 2 + 1) * numThreads));
    }
  }

  free(threads);
  free(threadIds);
  free(initElems);

  if (syncArg != '\0')
    free(waitTimes);
  
  exit(0);
}
