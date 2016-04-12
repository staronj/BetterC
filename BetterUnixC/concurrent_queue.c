/**
 * Copyright Jakub Staroń 2016
 */

#include "concurrent_queue.h"
#include <assert.h>
#include "safe_memory_operations.h"
#include "mutex_and_signal.h"
#include "queue.h"


struct ConcurrentQueue {
  MutexAndSignal_pointer mutex_signal;
  Queue_pointer queue;
};

ConcurrentQueue_pointer ConcurrentQueue_create() {
  ConcurrentQueue_pointer this = new(struct ConcurrentQueue);
  this->mutex_signal = MutexAndSignal_create();
  this->queue = Queue_create();
  return this;
}

void ConcurrentQueue_push(ConcurrentQueue_pointer this, void* pointer) {
  assert(this != NULL);
  MutexAndSignal_lock(this->mutex_signal);
  Queue_push(this->queue, pointer);
  MutexAndSignal_signal(this->mutex_signal);
  MutexAndSignal_unlock(this->mutex_signal);
}

void* ConcurrentQueue_pop(ConcurrentQueue_pointer this) {
  assert(this != NULL);
  MutexAndSignal_lock(this->mutex_signal);
  while (Queue_isEmpty(this->queue))
    MutexAndSignal_wait(this->mutex_signal);
  void* result = Queue_pop(this->queue);
  MutexAndSignal_unlock(this->mutex_signal);
  return result;
}

void ConcurrentQueue_destroy(ConcurrentQueue_pointer this) {
  assert(this != NULL);
  MutexAndSignal_destroy(this->mutex_signal);
  Queue_destroy(this->queue);
  free(this);
}
