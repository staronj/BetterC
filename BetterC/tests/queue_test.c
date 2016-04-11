/**
 * Copyright Jakub Staroń 2016
 */

#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "safe_memory_operations.h"


int main() {
  Queue_pointer queue = Queue_create();
  assert(Queue_isEmpty(queue) == true);
  assert(Queue_size(queue) == 0);

  for (int i = 0 ; i < 10 ; i++) {
    Queue_push(queue, new(int, i));
    assert(Queue_size(queue) == i + 1);
    assert(Queue_isEmpty(queue) == false);
  }

  int* foo;
  for (int i = 0 ; i < 10 ; i++) {
    foo = Queue_peek(queue);
    assert(*foo == i);
    assert(Queue_size(queue) == 10 - i);

    foo = Queue_pop(queue);
    assert(*foo == i);
    assert(Queue_size(queue) == 10 - i - 1);

    free(foo);
  }

  assert(Queue_isEmpty(queue) == true);
  assert(Queue_size(queue) == 0);

  Queue_push(queue, new(int, 42));

  assert(Queue_isEmpty(queue) == false);
  assert(Queue_size(queue) == 1);

  foo = Queue_pop(queue);
  free(foo);

  assert(Queue_isEmpty(queue) == true);
  assert(Queue_size(queue) == 0);

  Queue_destroy(queue);
}
