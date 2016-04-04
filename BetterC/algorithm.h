/**
 * Copyright Jakub Staroń 2016
 */

#ifndef BETTERC_ALGORITHM_H
#define BETTERC_ALGORITHM_H

#include <stdbool.h>
#include <stddef.h>

#define MIN(a, b) ((a)<=(b)?(a):(b))
#define MAX(a, b) ((a)>=(b)?(a):(b))


/**
 * Comparator function signature.
 *
 * Function takes two pointer to void which are pointers to arguments.
 *
 * When first argument is smaller should return -1.
 * When arguments are equal should return 0;
 * When second argument is smaller should return 1.
 */
typedef int (* ComparatorFunctionType)(const void*, const void*);

/**
 * Return signum of integet \p n.
 *
 * Signum is equal to -1 if n < 0, 0 if n == 0 and 1 if n > 0.
 */
int signum(int n);

/**
 * Sorts table.
 *
 * Sorts \p table with \p count elements of size \p elementSize with order defined by \p comparator.
 */
void sort(void* table, size_t count, size_t elementSize, ComparatorFunctionType comparator);

/**
 * Returns index to the first element in \p table which does not compare less than \p value.
 *
 * Returns \p count, if all elements are less.
 */
size_t lower_bound_index(const void* table, size_t count, size_t elementSize, const void* value,
                         ComparatorFunctionType comparator);

/**
 * Returns index to the first element in \p table which compares greater than \p value.
 *
 * Returns \p count, if all elements are not greater.
 */
size_t upper_bound_index(const void* table, size_t count, size_t elementSize, const void* value,
                         ComparatorFunctionType comparator);

/**
 * Test if value exists in sorted table.
 *
 * Returns true if any element in \p table is equivalent to \p value, and false otherwise.
 */
bool binary_search(const void* table, size_t count, size_t elementSize, const void* value,
                   ComparatorFunctionType comparator);

/**
 * Returns index of minimum element in \p table.
 *
 * \p Count must be positive.
 */
size_t minimum_element_index(const void* table, size_t count, size_t elementSize, ComparatorFunctionType comparator);

/**
 * Returns index of maximum element in \p table.
 *
 * \p Count must be positive.
 */
size_t maximum_element_index(const void* table, size_t count, size_t elementSize, ComparatorFunctionType comparator);

#endif /* BETTERC_ALGORITHM_H */
