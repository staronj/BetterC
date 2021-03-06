/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#include "thread.h"
#include <pthread.h>
#include <assert.h>
#include "safe_memory_operations.h"
#include "err.h"


struct Thread {
  pthread_t thread_id;
  enum ThreadType type;
};

Thread_pointer Thread_create(ThreadFunctionType function, void* args, enum ThreadType type) {
  pthread_attr_t attr;

  if (pthread_attr_init(&attr) != 0)
    syserr("Thread_create - pthread_attr_init failure.");

  pthread_attr_setdetachstate(&attr, (type == THREAD_JOINABLE)? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED);

  pthread_t thread_id;
  if (pthread_create(&thread_id, &attr, function, args) != 0)
    syserr("Thread_create - pthread_create failure.");

  Thread_pointer result = new(struct Thread);
  result->type = type;
  result->thread_id = thread_id;

  if (pthread_attr_destroy(&attr) != 0)
    syserr("Thread_create - pthread_attr_destroy failure.");

  return result;
}

enum ThreadType Thread_getType(Thread_pointer this) {
  assert(this != NULL);
  return this->type;
}

void Thread_detach(Thread_pointer this) {
  assert(this != NULL);

  if (this->type != THREAD_JOINABLE)
    fatal("Thread_detach - trying to detach already detached thread.");

  if (pthread_detach(this->thread_id) != 0)
    syserr("Thread_detach - pthread_detach failure.");

  this->type = THREAD_DETACHED;
}

void Thread_joinAndDestroy(Thread_pointer this, void** result) {
  assert(this != NULL);

  if (this->type != THREAD_JOINABLE)
    fatal("Thread_joinAndDestroy - trying to join non joinable thread.");

  if (pthread_join(this->thread_id, result) != 0)
    syserr("Thread_joinAndDestroy - pthread_join failure.");

  free(this);
}

void Thread_destroy(Thread_pointer this) {
  assert(this != NULL);

  if (this->type != THREAD_DETACHED)
    fatal("Thread_destroy - trying to free thread structure of not detached thread.");

  free(this);
}
