/**
 * Copyright Jakub Staroń 2016
 */

#ifndef BETTERC_CONCURRENT_QUEUE_H
#define BETTERC_CONCURRENT_QUEUE_H

/**
 * Concurrency-safe Queue of pointers.
 */
struct ConcurrentQueue;

typedef struct ConcurrentQueue* ConcurrentQueue_pointer;

/**
 * Creates new ConcurrentQueue.
 */
ConcurrentQueue_pointer ConcurrentQueue_create();

/**
 * Pushes \p pointer to the end of \p this queue.
 */
void ConcurrentQueue_push(ConcurrentQueue_pointer this, void* pointer);

/**
 * Pops and returns first element of \p this queue.
 * Waits if queue is empty.
 */
void* ConcurrentQueue_pop(ConcurrentQueue_pointer this);

/**
 * Destroys ConcurrentQueue.
 * Note, that usage of destroyed queue or destroying queue with someone waiting
 * behave in undefined way.
 */
void ConcurrentQueue_destroy(ConcurrentQueue_pointer this);

#endif /* BETTERC_CONCURRENT_QUEUE_H */
