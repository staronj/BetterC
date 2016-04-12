/**
 * Copyright Jakub Staroń 2016
 */

#include <assert.h>
#include "stack.h"
#include "safe_memory_operations.h"


int main() {
  Stack_pointer stack = Stack_create();
  assert(Stack_isEmpty(stack) == true);
  assert(Stack_size(stack) == 0);

  for (int i = 0 ; i < 100 ; i++) {
    Stack_push(stack, new(int, i));
    int* foo = Stack_peek(stack);
    assert(*foo == i);
    assert(Stack_size(stack) == i + 1);
    assert(Stack_isEmpty(stack) == false);
  }

  for (int i = 0 ; i < 100 ; i++) {
    int* foo = Stack_peek(stack);
    assert(*foo == 100 - i - 1);
    int* foo2 = Stack_pop(stack);
    assert(foo == foo2);
    free(foo);
  }

  assert(Stack_isEmpty(stack));
  assert(Stack_size(stack) == 0);

  Stack_push(stack, new(int, 0));
  Stack_push(stack, new(int, 1));
  free(Stack_pop(stack));
  Stack_push(stack, new(int, 2));

  assert(*(int*)Stack_peek(stack) == 2);
  free(Stack_pop(stack));
  free(Stack_pop(stack));

  assert(Stack_isEmpty(stack));
  assert(Stack_size(stack) == 0);

  Stack_destroy(stack);
  return 0;
}
