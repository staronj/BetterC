/**
 * Copyright Jakub Staroń 2016
 */

#ifndef BETTERC_READ_WRITE_LOCK_H
#define BETTERC_READ_WRITE_LOCK_H

#include <stdbool.h>

/**
 * ReadWriteLock structure.
 */
struct ReadWriteLock;

typedef struct ReadWriteLock* ReadWriteLock_pointer;

/**
 * Creates new ReadWriteLock.
 *
 * In case of failure calls syserr.
 */
ReadWriteLock_pointer ReadWriteLock_create();

/**
 *  Acquires read lock.
 */
void ReadWriteLock_readLock(ReadWriteLock_pointer this);

/**
 * Tries to acquire read lock.
 * If can not acquire lock immediately - returns.
 *
 * Returns true if read lock was acquired.
 */
bool ReadWriteLock_tryReadLock(ReadWriteLock_pointer this);

/**
 * Acquires write lock.
 */
void ReadWriteLock_writeLock(ReadWriteLock_pointer this);

/**
 * Tries to acquire write lock.
 * If can not acquire lock immediately - returns.
 *
 * Returns true if write lock was acquired.
 */
bool ReadWriteLock_tryWriteLock(ReadWriteLock_pointer this);

/**
 * Unlocks read or write lock.
 */
void ReadWriteLock_unlock(ReadWriteLock_pointer this);

/**
 * Destroys ReadWriteLock and frees memory.
 */
void ReadWriteLock_free(ReadWriteLock_pointer this);


#endif /* BETTERC_READ_WRITE_LOCK_H */
