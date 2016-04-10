/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#include "input_stream.h"
#include <assert.h>
#include "safe_memory_operations.h"


struct InputStream {
  String_pointer string;
  size_t i;
};

static InputStream_pointer InputStream_allocate() {
  return safe_raw_allocate(1, sizeof(struct InputStream));
}

InputStream_pointer InputStream_fromCString(const char* c_string) {
  InputStream_pointer result = InputStream_allocate();
  result->i = 0;
  result->string = String_fromCString(c_string);
  return result;
}

InputStream_pointer InputStream_fromString(String_pointer string) {
  InputStream_pointer result = InputStream_allocate();
  result->i = 0;
  result->string = String_clone(string);
  return result;
}

InputStream_pointer InputStream_fromData(const char* data, size_t size) {
  InputStream_pointer result = InputStream_allocate();
  result->i = 0;
  result->string = String_fromData(data, size);
  return result;
}

void InputStream_destroy(InputStream_pointer this) {
  assert(this != NULL);
  String_destroy(this->string);
  this->string = NULL;
  this->i = 0;
  free(this);
}

char InputStream_readChar(InputStream_pointer this) {
  assert(this != NULL);
  assert(InputStream_hasNext(this));
  char c = InputStream_peekChar(this);
  this->i++;
  return c;
}

char InputStream_peekChar(InputStream_pointer this) {
  assert(this != NULL);
  assert(InputStream_hasNext(this));
  return String_at(this->string, this->i);
}

void InputStream_readData(InputStream_pointer this, void* output, size_t size) {
  assert(this != NULL);
  assert(InputStream_howManyMore(this) >= size);

  safe_raw_copy(output, String_data(this->string) + this->i, size, sizeof(char));
  this->i += size;
}

String_pointer InputStream_readAll(InputStream_pointer this) {
  assert(this != NULL);
  return InputStream_readAtMost(this, String_size(this->string));
}

String_pointer InputStream_readAtMost(InputStream_pointer this, size_t count) {
  assert(this != NULL);
  size_t available = InputStream_howManyMore(this);
  if (available < count)
    count = available;

  const char* data = String_data(this->string) + this->i;
  String_pointer result = String_fromData(data, count);
  this->i += count;

  return result;
}

int InputStream_readRawInt(InputStream_pointer this) {
  assert(this != NULL);
  int result = 0;
  InputStream_readData(this, &result, sizeof(int));
  return result;
}

bool InputStream_hasNext(InputStream_pointer this) {
  assert(this != NULL);
  return this->i < String_size(this->string);
}

size_t InputStream_howManyMore(InputStream_pointer this) {
  assert(this != NULL);
  return String_size(this->string) - this->i;
}
