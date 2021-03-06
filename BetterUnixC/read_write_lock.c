/**
 * Copyright Jakub Staroń 2016
 */

#include "read_write_lock.h"
#include <errno.h>
#include <pthread.h>
#include <assert.h>
#include "safe_memory_operations.h"
#include "err.h"


struct ReadWriteLock {
  pthread_rwlock_t rwlock;
};

ReadWriteLock_pointer ReadWriteLock_create() {
  ReadWriteLock_pointer this = new(struct ReadWriteLock);

  if (pthread_rwlock_init(&this->rwlock, NULL) != 0)
    syserr("ReadWriteLock_create - pthread_rwlock_init failure.");

  return this;
}

void ReadWriteLock_readLock(ReadWriteLock_pointer this) {
  assert(this != NULL);

  if (pthread_rwlock_rdlock(&this->rwlock) != 0)
    syserr("ReadWriteLock_readLock - pthread_rwlock_rdlock failure.");
}

bool ReadWriteLock_tryReadLock(ReadWriteLock_pointer this) {
  assert(this != NULL);

  int result = pthread_rwlock_tryrdlock(&this->rwlock);

  if (result != 0 && result != EBUSY)
    syserr("ReadWriteLock_tryReadLock - pthread_rwlock_tryrdlock failure.");
  if (result == EBUSY)
    return false;
  else
    return true;
}

void ReadWriteLock_writeLock(ReadWriteLock_pointer this) {
  assert(this != NULL);

  if (pthread_rwlock_wrlock(&this->rwlock) != 0)
    syserr("ReadWriteLock_readLock - pthread_rwlock_rdlock failure.");
}

bool ReadWriteLock_tryWriteLock(ReadWriteLock_pointer this) {
  assert(this != NULL);

  int result = pthread_rwlock_trywrlock(&this->rwlock);

  if (result != 0 && result != EBUSY)
    syserr("ReadWriteLock_tryWriteLock - pthread_rwlock_trywrlock failure.");
  if (result == EBUSY)
    return false;
  else
    return true;
}

void ReadWriteLock_unlock(ReadWriteLock_pointer this) {
  assert(this != NULL);

  if (pthread_rwlock_unlock(&this->rwlock) != 0)
    syserr("ReadWriteLock_unlock - pthread_rwlock_unlock failure.");
}

void ReadWriteLock_destroy(ReadWriteLock_pointer this) {
  assert(this != NULL);

  if (pthread_rwlock_destroy(&this->rwlock) != 0)
    syserr("ReadWriteLock_destroy - pthread_rwlock_destroy failure.");

  free(this);
}
