/**
 * Copyright Jakub Staroń 2016
 */

#include <assert.h>
#include <string.h>
#include "input_stream.h"

int main() {
  const char* text = "Hello World!";

  /* Construction */
  InputStream_pointer stream1 = InputStream_fromCString(text);

  String_pointer string = String_fromCString(text);
  InputStream_pointer stream2 = InputStream_fromString(string);
  String_destroy(string);

  InputStream_pointer stream3 = InputStream_fromData(text, strlen(text));

  /* Proper size */
  assert(InputStream_howManyMore(stream1) == 12);
  assert(InputStream_howManyMore(stream2) == 12);
  assert(InputStream_howManyMore(stream3) == 12);

  assert(InputStream_hasNext(stream1) == true);
  assert(InputStream_readChar(stream1) == 'H');
  char temp[5];
  InputStream_readData(stream1, temp, 5);
  assert(memcmp(temp, "ello ", 5) == 0);

  String_pointer rest = InputStream_readAll(stream1);
  assert(String_compareCstr(rest, "World!") == 0);
  assert(InputStream_howManyMore(stream1) == 0);
  assert(InputStream_hasNext(stream1) == false);

  /* Reading integer */
  int test_int = 12345;
  InputStream_pointer stream4 = InputStream_fromData((const char*) &test_int, sizeof(int));
  int received_int = InputStream_readRawInt(stream4);
  assert(test_int == received_int);
  assert(InputStream_hasNext(stream4) == false);

  /* Destruction */
  InputStream_destroy(stream1);
  InputStream_destroy(stream2);
  InputStream_destroy(stream3);
  InputStream_destroy(stream4);
}