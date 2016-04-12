/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#ifndef BETTERC_STACK_H
#define BETTERC_STACK_H

#include <stddef.h>
#include <stdbool.h>


/**
 * Structure Stack.
 *
 * FILO container for void* pointers.
 */
struct Stack;

typedef struct Stack* Stack_pointer;

/**
 * Creates new, empty Stack.
 */
Stack_pointer Stack_create();

/**
 * Returns true if \p this Stack is empty.
 */
bool Stack_isEmpty(Stack_pointer this);

/**
 * Returns size of \p this Stack.
 */
size_t Stack_size(Stack_pointer this);

/**
 * Inserts \p pointer at the top of \p this Stack.
 */
void Stack_push(Stack_pointer this, void* pointer);

/**
 * Returns top element of \p this Stack without removing it.
 */
void* Stack_peek(Stack_pointer this);

/**
 * Returns top element of \p this Stack and removes it.
 */
void* Stack_pop(Stack_pointer this);

/**
 * Destroys \p this Stack.
 *
 * Note, that memory pointed by pointers stored in the Stack is not released.
 */
void Stack_destroy(Stack_pointer this);

#endif /* BETTERC_STACK_H */
