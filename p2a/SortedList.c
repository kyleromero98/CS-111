// NAME: Kyle Romero
// EMAIL: kyleromero98@gmail.com
// ID: 204747283

#include "SortedList.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void SortedList_insert(SortedList_t *list, SortedListElement_t *element) {
  if (list == NULL || element == NULL)
    return;

  SortedListElement_t* currElem = list->next;

  while (currElem != list) {
    if (strcmp(element->key, currElem->key) <= 0)
      break;

    currElem = currElem->next;
  }
  
  if(opt_yield & INSERT_YIELD)
    sched_yield();
  
  element->next = currElem;
  element->prev = currElem->prev;
  currElem->prev->next = element;
  currElem->prev = element;
  return;
}

int SortedList_delete(SortedListElement_t *element) {
  // invalid argument or trying to delete head is bad
  if (element == NULL || element->key == NULL)
    return 1;
  // checking for corrupt
  if (element->prev->next != element || element->next->prev != element)
    return 1;

  if (opt_yield & DELETE_YIELD)
    sched_yield();

  // move things around element to delete
  element->prev->next = element->next;
  element->next->prev = element->prev;
  return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key) {
  if (list == NULL || list->key != NULL)
    return NULL; 
  
  SortedListElement_t *currElem = list->next;
  while (currElem != list) {
    // we found the element
    if (!strcmp(key, currElem->key))
      return currElem;
    if (opt_yield & LOOKUP_YIELD)
      sched_yield();
    currElem = currElem->next;
  }
  // we didnt find element
  return NULL; 
}

int SortedList_length(SortedList_t *list) {
  int length = 0;

  // invalid argument or invalid key for head
  if (list == NULL)
    return -1;

  // save the greatest element
  SortedListElement_t *currElem = list->next;

  // while we aren't at the head
  while (currElem != list) {
    // check for corruption
    if (currElem->prev->next != currElem || currElem->next->prev != currElem)
      return -2;
    length++;
    // yield if necessary
    if (opt_yield & LOOKUP_YIELD)
      sched_yield();
    currElem = currElem->next;
  }
  return length;
}
