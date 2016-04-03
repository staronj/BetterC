/**
 * Copyright Jakub Staroń 2015
 */

#ifndef PROJECT_MUTEX_AND_SIGNAL_H
#define PROJECT_MUTEX_AND_SIGNAL_H

/**
 * Pair of pthread mutex and condition variable.
 *
 * Useful for implementing simple monitors.
 */
struct MutexAndSignal;

typedef struct MutexAndSignal* MutexAndSignal_pointer;

/**
 * Creates new mutex and condition variable pair.
 * In case of failure calls syserr.
 */
MutexAndSignal_pointer MutexAndSignal_create();

/**
 * Locks mutex.
 * In case of failure calls syserr.
 */
void MutexAndSignal_lock(MutexAndSignal_pointer this);

/**
 * Unlocks mutex.
 * In case of failure calls syserr.
 */
void MutexAndSignal_unlock(MutexAndSignal_pointer this);

/**
 * Waits on condition variable.
 * In case of failure calls syserr.
 */
void MutexAndSignal_wait(MutexAndSignal_pointer this);

/**
 *  Signals condition variable.
 *  In case of failure calls syserr.
 */
void MutexAndSignal_signal(MutexAndSignal_pointer this);

/**
 * Free mutex, condition variable and memory.
 * In case of failure calls syserr.
 */
void MutexAndSignal_free(MutexAndSignal_pointer this);

#endif //PROJECT_MUTEX_AND_SIGNAL_H
