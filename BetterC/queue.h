/**
 * Copyright Jakub Staroń 2016
 */

#ifndef BETTERC_QUEUE_H
#define BETTERC_QUEUE_H

#include <stdbool.h>
#include <stddef.h>


/**
 * Structure Queue.
 *
 * FIFO container for void* pointers.
 */
struct Queue;

typedef struct Queue* Queue_pointer;

/**
 * Creates new, empty Queue.
 */
Queue_pointer Queue_create();

/**
 * Returns true if \p this Queue is empty.
 */
bool Queue_isEmpty(Queue_pointer this);

/**
 * Returns size of \p this Queue.
 */
size_t Queue_size(Queue_pointer this);

/**
 * Inserts \p pointer at the end of \p this Queue.
 */
void Queue_push(Queue_pointer this, void* pointer);

/**
 * Returns first element of \p this Queue without removing it.
 */
void* Queue_peek(Queue_pointer this);

/**
 * Returns first element of \p this Queue and removes it.
 */
void* Queue_pop(Queue_pointer this);

/**
 * Destroys \p this Queue.
 *
 * Note, that memory pointed by pointers stored in the queue is not released.
 */
void Queue_destroy(Queue_pointer this);

#endif /* BETTERC_QUEUE_H */
