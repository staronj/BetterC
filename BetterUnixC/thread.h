/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#ifndef BETTERC_THREAD_H
#define BETTERC_THREAD_H

/**
 * Thread structure.
 */
struct Thread;

typedef struct Thread* Thread_pointer;

typedef void* (* ThreadFunctionType)(void*);

enum ThreadType {
  THREAD_JOINABLE, THREAD_DETACHED
};

/**
 * Creates and runs new thread.
 * \p Function is thread function address.
 * \p Args will be pass as arguments to this function.
 * For more info about \p type see enum ThreadType.
 * In case of failure calls syserr.
 */
Thread_pointer Thread_create(ThreadFunctionType function, void* args, enum ThreadType type);

/**
 * Returns ThreadType of \p this thread.
 */
enum ThreadType Thread_getType(Thread_pointer this);

/**
 * Makes \p this thread detached.
 *
 * Thread must have THREAD_JOINABLE type.
 * After this call thread will have THREAD_DETACHED type.
 */
void Thread_detach(Thread_pointer this);

/**
 * Joins thread and frees memory.
 *
 * Thread must be joinable otherwise fatal will be called.
 *
 * \p Result should be pointer to memory where return code will be copied.
 * Ignored if NULL.
 *
 * In case of failure calls syserr.
 */
void Thread_joinAndDestroy(Thread_pointer this, void** result);

/**
 * Frees memory.
 *
 * Thread must be in detached state otherwise fatal will be called.
 */
void Thread_destroy(Thread_pointer this);

#endif /* BETTERC_THREAD_H */
