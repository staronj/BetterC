/**
 * Copyright Jakub Staroń 2016
 */

#include "algorithm.h"

#include <assert.h>
#include <string.h>

void test_min() {
  assert(MIN(1, 2) == 1);
}

void test_max() {
  assert(MAX(1, 2) == 2);
}

void test_signum() {
  assert(signum(-100) == -1);
  assert(signum(-1) == -1);
  assert(signum(0) == 0);
  assert(signum(1) == 1);
  assert(signum(42) == 1);
}

int Comparator_int(const void* a, const void* b) {
  return signum(*(int*)a - *(int*)b);
}

void test_sort() {
  int table1[] = {1, 4, 8, 1, 3, 2, 1};
  int table2[] = {1, 1, 1, 2, 3, 4, 8};
  sort(table1, 7, sizeof(int), Comparator_int);

  assert(memcmp(table1, table2, sizeof(table1)) == 0);
}

void test_lower_upper_bound() {
  int table[] = {1, 1, 2, 2, 3, 3, 3, 8, 9, 10, 11, 11};

  int value = 1;
  assert(lower_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 0);
  assert(upper_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 2);
  value = 100;
  assert(lower_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 12);
  assert(upper_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 12);
  value = 2;
  assert(lower_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 2);
  assert(upper_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 4);
  value = 3;
  assert(lower_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 4);
  assert(upper_bound_index(table, 12, sizeof(int), &value, Comparator_int) == 7);
}

void test_binary_search() {
  int table[] = {1, 2, 2, 3, 5, 10, 11, 12, 12, 100};
  const size_t table_size = sizeof(table) / sizeof(int);

  int value = 0;
  assert(binary_search(table, table_size, sizeof(int), &value, Comparator_int) == false);
  value = 1;
  assert(binary_search(table, table_size, sizeof(int), &value, Comparator_int) == true);
  value = 2;
  assert(binary_search(table, table_size, sizeof(int), &value, Comparator_int) == true);
  value = 4;
  assert(binary_search(table, table_size, sizeof(int), &value, Comparator_int) == false);
  value = 100;
  assert(binary_search(table, table_size, sizeof(int), &value, Comparator_int) == true);
  value = 101;
  assert(binary_search(table, table_size, sizeof(int), &value, Comparator_int) == false);
}

void test_minimum_maximum_element() {
  int table[] = {1, 8, 3, 1, -1, 2, 100, -100, 3, 3};
  assert(minimum_element_index(table, 10, sizeof(int), Comparator_int) == 7);
  assert(maximum_element_index(table, 10, sizeof(int), Comparator_int) == 6);
}

int main() {
  test_min();
  test_max();
  test_signum();
  test_sort();
  test_lower_upper_bound();
  test_binary_search();
  test_minimum_maximum_element();
  return 0;
}