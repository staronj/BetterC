/**
 * Copyright Jakub Staroń 2016
 */

#include "thread_pool.h"
#include <assert.h>
#include "concurrent_queue.h"
#include "safe_memory_operations.h"
#include "thread.h"


struct ThreadPool {
  ConcurrentQueue_pointer queue;
  size_t threads_count;
  Thread_pointer* threads;
};

struct ThreadPoolWork {
  ThreadPoolFunctionType function;
  void* arguments;
};

typedef struct ThreadPoolWork* ThreadPoolWork_pointer;

void* ThreadPoolWorker(void* arg) {
  ThreadPool_pointer this = arg;

  ThreadPoolWork_pointer work = ConcurrentQueue_pop(this->queue);
  while (work != NULL) {
    work->function(work->arguments);
    free(work);
    work = ConcurrentQueue_pop(this->queue);
  }
  return NULL;
}

ThreadPool_pointer ThreadPool_create(size_t threads) {
  ThreadPool_pointer this = new(struct ThreadPool);
  this->queue = ConcurrentQueue_create();
  this->threads_count = threads;
  this->threads = new_table(Thread_pointer, this->threads_count);

  for (size_t i = 0 ; i < this->threads_count ; i++)
    this->threads[i] = Thread_create(ThreadPoolWorker, this, THREAD_JOINABLE);

  return this;
}

void ThreadPool_push(ThreadPool_pointer this, ThreadPoolFunctionType function, void* arguments) {
  assert(this != NULL);
  assert(function != NULL);
  ThreadPoolWork_pointer work = new(struct ThreadPoolWork, .function=function, .arguments=arguments);
  ConcurrentQueue_push(this->queue, work);
}

void ThreadPool_joinAndDestroy(ThreadPool_pointer this) {
  assert(this != NULL);

  for (size_t i = 0 ; i < this->threads_count ; i++)
    ConcurrentQueue_push(this->queue, NULL);

  for (size_t i = 0 ; i < this->threads_count ; i++)
    Thread_joinAndDestroy(this->threads[i], NULL);

  free(this->threads);
  ConcurrentQueue_destroy(this->queue);
  free(this);
}