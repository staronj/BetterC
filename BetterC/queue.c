/**
 * Copyright Jakub Staroń 2016
 */

#include "queue.h"
#include <assert.h>
#include "safe_memory_operations.h"
#include "err.h"


struct QueueNode;

typedef struct QueueNode* QueueNode_pointer;

struct QueueNode {
  QueueNode_pointer next;
  void* value;
};

static QueueNode_pointer QueueNode_allocate() {
  return safe_raw_allocate(1, sizeof(struct QueueNode));
}

struct Queue {
  size_t size;
  QueueNode_pointer first;
  QueueNode_pointer last;
};

static Queue_pointer Queue_allocate() {
  return safe_raw_allocate(1, sizeof(struct Queue));
}

Queue_pointer Queue_create() {
  Queue_pointer this = Queue_allocate();
  return this;
}

bool Queue_isEmpty(Queue_pointer this) {
  assert(this != NULL);
  return this->first == NULL;
}

size_t Queue_size(Queue_pointer this) {
  assert(this != NULL);
  return this->size;
}

void Queue_push(Queue_pointer this, void* pointer) {
  assert(this != NULL);
  QueueNode_pointer node = QueueNode_allocate();
  node->value = pointer;

  if (this->last == NULL) {
    this->first = node;
    this->last = node;
  }
  else {
    this->last->next = node;
    this->last = node;
  }

  this->size++;
}

void* Queue_peek(Queue_pointer this) {
  assert(this != NULL);

  if (Queue_isEmpty(this))
    fatal("Queue_peek - empty Queue.");

  return this->first->value;
}

void* Queue_pop(Queue_pointer this) {
  assert(this != NULL);

  if (Queue_isEmpty(this))
    fatal("Queue_pop - empty Queue.");

  QueueNode_pointer node = this->first;
  this->first = node->next;
  if (this->first == NULL)
    this->last = NULL;

  void* result = node->value;
  free(node);
  this->size--;
  return result;
}

void Queue_destroy(Queue_pointer this) {
  assert(this != NULL);
  while (!Queue_isEmpty(this))
    Queue_pop(this);

  free(this);
}