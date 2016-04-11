/**
 * Copyright Jakub Staroń 2016
 */

#include <stdio.h>
#include <unistd.h>
#include "safe_memory_operations.h"
#include "concurrent_queue.h"
#include "thread_pool.h"


ConcurrentQueue_pointer queue;

void Producer(void* arg) {
  int* thread_id = arg;
  for (int i = 0 ; i < 5 ; i++) {
    sleep(1);
    printf("Producer %d: producing <%d>\n", *thread_id, i);
    ConcurrentQueue_push(queue, new(int, i));
  }
  free(thread_id);
}

void Consumer(void* arg) {
  int* thread_id = arg;
  for (int i = 0 ; i < 5 ; i++) {
    int* foo = ConcurrentQueue_pop(queue);
    printf("Consumer %d: consuming <%d>\n", *thread_id, *foo);
    free(foo);
  }
  free(thread_id);
}

int main() {
  queue = ConcurrentQueue_create();

  ThreadPool_pointer thread_pool = ThreadPool_create(4);
  ThreadPool_push(thread_pool, Producer, new(int, 1));
  ThreadPool_push(thread_pool, Producer, new(int, 2));
  ThreadPool_push(thread_pool, Consumer, new(int, 1));
  ThreadPool_push(thread_pool, Consumer, new(int, 2));

  ThreadPool_joinAndDestroy(thread_pool);
  ConcurrentQueue_destroy(queue);
  return 0;
}
