/**
 * Copyright Jakub Staroń 2015
 */

#ifndef BETTERC_THREAD_H
#define BETTERC_THREAD_H


/**
 * Pthread thread.
 */
struct Thread;

typedef struct Thread* Thread_pointer;
typedef void* (*Thread_function_type)(void*);

/**
 * Creates and runs new thread.
 * \p Function is thread function address.
 * \p Args will be pass as arguments to this function.
 * \p Joinable is toggling between joinable or detached state of thread.
 * In case of failure calls syserr.
 */
Thread_pointer Thread_create(Thread_function_type function, void* args, bool joinable);

/**
 * Joins thread and frees memory.
 *
 * \p Result should be pointer to memory where return code will be copied.
 * Ignored if NULL.
 *
 * In case of failure calls syserr.
 */
void Thread_joinAndFree(Thread_pointer this, void** result);

/**
 * Frees memory.
 *
 * Thread should be in detached state, otherwise zombie will be created!
 */
void Thread_free(Thread_pointer this);


#endif /* BETTERC_THREAD_H */
