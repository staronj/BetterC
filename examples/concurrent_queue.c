/**
 * Copyright Jakub Staroń 2016
 */

#include <stdio.h>
#include <unistd.h>
#include "safe_memory_operations.h"
#include "concurrent_queue.h"
#include "thread.h"


ConcurrentQueue_pointer queue;

void* Producer(void* arg) {
  int* thread_id = arg;
  for (int i = 0 ; i < 5 ; i++) {
    sleep(1);
    printf("Producer %d: producing %d\n", *thread_id, i);
    ConcurrentQueue_push(queue, new(int, i));
  }
  free(thread_id);
  return NULL;
}

void* Consumer(void* arg) {
  int* thread_id = arg;
  for (int i = 0 ; i < 5 ; i++) {
    int* foo = ConcurrentQueue_pop(queue);
    printf("Consumer %d: consuming %d\n", *thread_id, *foo);
    free(foo);
  }
  free(thread_id);
  return NULL;
}

int main() {
  queue = ConcurrentQueue_create();

  Thread_pointer producer1 = Thread_create(Producer, new(int, 1), THREAD_JOINABLE);
  Thread_pointer producer2 = Thread_create(Producer, new(int, 2), THREAD_JOINABLE);
  Thread_pointer consumer1 = Thread_create(Consumer, new(int, 1), THREAD_JOINABLE);
  Thread_pointer consumer2 = Thread_create(Consumer, new(int, 2), THREAD_JOINABLE);

  Thread_joinAndDestroy(producer1, NULL);
  Thread_joinAndDestroy(producer2, NULL);
  Thread_joinAndDestroy(consumer1, NULL);
  Thread_joinAndDestroy(consumer2, NULL);

  ConcurrentQueue_destroy(queue);
  return 0;
}
