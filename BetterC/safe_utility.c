/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#include "safe_utility.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "safe_memory_operations.h"
#include "err.h"


long safe_cstring_to_long(const char* text) {
  errno = 0;
  long result = strtol(text, NULL, 10);
  if (errno != 0)
    fatal("safe_cstring_to_long: conversion of \"%s\" to long failed.", text);
  return result;
}

long safe_cstring_to_long_min_max(const char* text, long minimal, long maximal) {
  long result = safe_cstring_to_long(text);
  if (maximal < result || result < minimal)
    fatal("safe_cstring_to_long_min_max: %ld is not in range <%ld, %ld>.", result, minimal, maximal);
  return result;
}

void** safe_allocate_2d_array(size_t first_size, size_t second_size, size_t element_size) {
  void** result = safe_raw_allocate(first_size, sizeof(void*));
  for (size_t i = 0 ; i < first_size ; i++) {
    result[i] = safe_raw_allocate(second_size, element_size);
  }
  return result;
}

void safe_deallocate_2d_array(void** pointer, size_t first_size) {
  if (pointer == NULL)
    return;

  for (size_t i = 0 ; i < first_size ; i++) {
    free(pointer[i]);
    pointer[i] = NULL;
  }
  free(pointer);
}

String_pointer safe_int_to_string(int n) {
  char tmp[20];
  sprintf(tmp, "%d", n);
  return String_fromCString(tmp);
}
