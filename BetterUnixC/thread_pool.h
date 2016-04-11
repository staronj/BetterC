/**
 * Copyright Jakub Staroń 2016
 */

#ifndef BETTERC_THREAD_POOL_H
#define BETTERC_THREAD_POOL_H

#include <stddef.h>


/**
 * ThreadPool structure.
 */
struct ThreadPool;

typedef struct ThreadPool* ThreadPool_pointer;

/**
 * Signature of allowed work function.
 */
typedef void (* ThreadPoolFunctionType)(void*);

/**
 * Creates new thread pool.
 */
ThreadPool_pointer ThreadPool_create(size_t threads);

/**
 * Pushes new work into ThreadPool.
 *
 * Function is thread-safe.
 */
void ThreadPool_push(ThreadPool_pointer this, ThreadPoolFunctionType function, void* arguments);

/**
 * Waits for all workers to finish jobs and destroys ThreadPool.
 */
void ThreadPool_joinAndDestroy(ThreadPool_pointer this);

#endif /* BETTERC_THREAD_POOL_H */
