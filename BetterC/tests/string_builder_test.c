/**
 * Copyright Jakub Staroń 2016
 */

#include <assert.h>
#include <string.h>
#include "string_builder.h"




void create_empty_test() {
  StringBuilder_pointer builder = StringBuilder_createEmpty();
  assert(StringBuilder_size(builder) == 0);
  assert(StringBuilder_empty(builder) == true);

  StringBuilder_appendChar(builder, 'H');
  StringBuilder_appendChar(builder, 'e');
  StringBuilder_appendCString(builder, "llo ");
  StringBuilder_appendData(builder, "Wor", 3);

  String_pointer string = String_fromCString("ld!");
  StringBuilder_appendString(builder, string);
  String_destroy(string);

  string = StringBuilder_toString(builder);
  assert(String_compareCstr(string, "Hello World!") == 0);

  StringBuilder_clear(builder);
  assert(StringBuilder_empty(builder) == true);
  assert(StringBuilder_size(builder) == 0);

  StringBuilder_destroy(builder);
}

void from_various_test() {
  const char* text = "Hello World!";

  StringBuilder_pointer builder1 = StringBuilder_fromCString(text);
  StringBuilder_pointer builder2 = StringBuilder_fromData(text, strlen(text));

  String_pointer string = String_fromCString(text);
  StringBuilder_pointer builder3 = StringBuilder_fromString(string);
  String_destroy(string);

  assert(StringBuilder_size(builder1) == 12);
  assert(StringBuilder_size(builder2) == 12);
  assert(StringBuilder_size(builder3) == 12);

  assert(memcmp(StringBuilder_data(builder1), text, 12) == 0);
  assert(memcmp(StringBuilder_data(builder2), text, 12) == 0);
  assert(memcmp(StringBuilder_data(builder3), text, 12) == 0);

  StringBuilder_destroy(builder1);
  StringBuilder_destroy(builder2);
  StringBuilder_destroy(builder3);
}

void append_string_test() {
  StringBuilder_pointer builder = StringBuilder_createEmpty();

  StringBuilder_appendFormattedInt(builder, 123456789);
  String_pointer string = StringBuilder_toString(builder);
  assert(String_compareCstr(string, "123456789") == 0);
  String_destroy(string);

  StringBuilder_clear(builder);
  int value = 123456789;
  StringBuilder_appendRawInt(builder, value);
  assert(memcmp(StringBuilder_data(builder), &value, sizeof(int)) == 0);

  StringBuilder_destroy(builder);
}

static bool equal_to(StringBuilder_pointer builder, const char* text) {
  String_pointer string = StringBuilder_toString(builder);
  bool result = (String_compareCstr(string, text) == 0);
  String_destroy(string);
  return result;
}

void insert_test() {
  const char* text = "Hello World!";
  StringBuilder_pointer builder = StringBuilder_fromCString(text);

  StringBuilder_insertChar(builder, 0, '!');
  assert(equal_to(builder, "!Hello World!"));

  StringBuilder_insertChar(builder, 13, '1');
  assert(equal_to(builder, "!Hello World!1"));

  StringBuilder_clear(builder);
  StringBuilder_insertCString(builder, 0, text);
  StringBuilder_insertCString(builder, 5, text);
  assert(equal_to(builder, "HelloHello World! World!"));

  StringBuilder_clear(builder);
  StringBuilder_insertData(builder, 0, text, strlen(text));
  StringBuilder_insertData(builder, strlen(text), text, strlen(text));
  assert(equal_to(builder, "Hello World!Hello World!"));

  String_pointer string = String_fromCString(" lovely");
  StringBuilder_insertString(builder, 5, string);
  String_destroy(string);
  assert(equal_to(builder, "Hello lovely World!Hello World!"));

  StringBuilder_destroy(builder);
}

int main() {
  create_empty_test();
  from_various_test();
  append_string_test();
  insert_test();
}
