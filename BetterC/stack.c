/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#include "stack.h"
#include <assert.h>
#include "safe_memory_operations.h"
#include "err.h"


struct StackNode;

typedef struct StackNode* StackNode_pointer;

struct StackNode {
  StackNode_pointer next;
  void* value;
};

struct Stack {
  size_t size;
  StackNode_pointer top;
};

Stack_pointer Stack_create() {
  Stack_pointer this = new(struct Stack);
  return this;
}

bool Stack_isEmpty(Stack_pointer this) {
  assert(this != NULL);
  return this->top == NULL;
}

size_t Stack_size(Stack_pointer this) {
  assert(this != NULL);
  return this->size;
}

void Stack_push(Stack_pointer this, void* pointer) {
  assert(this != NULL);
  StackNode_pointer node = new(struct StackNode);
  node->value = pointer;
  node->next = this->top;
  this->top = node;
  this->size++;
}

void* Stack_peek(Stack_pointer this) {
  assert(this != NULL);

  if (Stack_isEmpty(this))
    fatal("Stack_peek - empty Stack.");

  return this->top->value;
}

void* Stack_pop(Stack_pointer this) {
  assert(this != NULL);

  if (Stack_isEmpty(this))
    fatal("Stack_pop - empty Stack.");

  StackNode_pointer node = this->top;
  this->top = node->next;
  void* result = node->value;
  free(node);
  this->size--;
  return result;
}

void Stack_destroy(Stack_pointer this) {
  assert(this != NULL);
  while (!Stack_isEmpty(this))
    Stack_pop(this);

  free(this);
}
