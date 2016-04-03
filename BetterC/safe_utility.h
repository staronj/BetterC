/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#ifndef BETTERC_SAFE_UTILITY_H
#define BETTERC_SAFE_UTILITY_H

#include "better_string.h"

#include <stddef.h>

/**
 * Performs safe conversion from c string to integer.
 * If fails, fail function is called.
 * Second version have additional parameters to assert integer range.
 */
long safe_cstring_to_long(const char*);
long safe_cstring_to_long_min_max(const char*, long, long);

/**
 * Allocates and deallocates 2d arrays.
 */
void** safe_allocate_2d_array(size_t first_size, size_t second_size, size_t element_size);
void safe_deallocate_2d_array(void** pointer, size_t first_size);

/**
 * Converts int to string.
 */
String_pointer safe_int_to_string(int);

#endif /* BETTERC_SAFE_UTILITY_H */
