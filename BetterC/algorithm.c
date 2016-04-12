/**
 * Copyright Jakub Staroń 2016
 */

#include "algorithm.h"
#include <stdlib.h>
#include <assert.h>
#include "safe_memory_operations.h"


int signum(int n) {
  return (n < 0)? -1 : ((n > 0)? 1 : 0);
}

void sort(void* table, size_t count, size_t elementSize, ComparatorFunctionType comparator) {
  assert(table != NULL);
  assert(comparator != NULL);
  assert(elementSize > 0);

  qsort(table, count, elementSize, comparator);
}

size_t lower_bound_index(const void* table, size_t count, size_t elementSize, const void* value,
                         ComparatorFunctionType comparator) {
  assert(table != NULL);
  assert(value != NULL);
  assert(comparator != NULL);
  assert(elementSize > 0);

  size_t begin = 0;
  size_t end = count;
  /* Invariant: result is in range [being, end] */
  while (begin < end) {
    /* Because its integer division, middle is always less than end if begin < end. */
    size_t middle = (begin + end) / 2;
    const void* element = safe_raw_offset((void*)table, middle, elementSize);
    int compare = comparator(element, value);
    if (compare < 0)
      begin = middle + 1;
    else
      end = middle;
  }
  return begin;
}

size_t upper_bound_index(const void* table, size_t count, size_t elementSize, const void* value,
                         ComparatorFunctionType comparator) {
  assert(table != NULL);
  assert(value != NULL);
  assert(comparator != NULL);
  assert(elementSize > 0);

  size_t begin = 0;
  size_t end = count;
  /* Invariant: result is in range [being, end] */
  while (begin < end) {
    /* Because its integer division, middle is always less than end if begin < end. */
    size_t middle = (begin + end) / 2;
    const void* element = safe_raw_offset((void*)table, middle, elementSize);
    int compare = comparator(element, value);
    if (compare <= 0)
      begin = middle + 1;
    else
      end = middle;
  }
  return begin;
}

bool binary_search(const void* table, size_t count, size_t elementSize, const void* value,
                   ComparatorFunctionType comparator) {
  assert(table != NULL);
  assert(value != NULL);
  assert(comparator != NULL);
  assert(elementSize > 0);

  size_t index = lower_bound_index(table, count, elementSize, value, comparator);
  void* element = safe_raw_offset((void*)table, index, elementSize);
  return (0 < count && index < count && comparator(value, element) == 0);
}

size_t minimum_element_index(const void* table, size_t count, size_t elementSize, ComparatorFunctionType comparator) {
  assert(table != NULL);
  assert(count > 0);
  assert(comparator != NULL);
  assert(elementSize > 0);

  const void* element = table;
  size_t index = 0;
  for (size_t i = 1 ; i < count ; i++) {
    const void* new_element = safe_raw_offset((void*)table, i, elementSize);
    if (comparator(new_element, element) < 0) {
      index = i;
      element = new_element;
    }
  }
  return index;
}

size_t maximum_element_index(const void* table, size_t count, size_t elementSize, ComparatorFunctionType comparator) {
  assert(table != NULL);
  assert(count > 0);
  assert(comparator != NULL);
  assert(elementSize > 0);

  const void* element = table;
  size_t index = 0;
  for (size_t i = 1 ; i < count ; i++) {
    const void* new_element = safe_raw_offset((void*)table, i, elementSize);
    if (comparator(element, new_element) < 0) {
      index = i;
      element = new_element;
    }
  }
  return index;
}
