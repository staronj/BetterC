/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#ifndef BETTERC_BETTER_STRING_H
#define BETTERC_BETTER_STRING_H

#include <stddef.h>
#include <stdbool.h>

/**
 * Immutable string.
 */
struct String;

typedef struct String* String_pointer;

/**
 * Constructs new string from \p data, \p c_string or another \p string.
 */
String_pointer String_fromData(const char* data, size_t size);

String_pointer String_fromCString(const char* c_string);

String_pointer String_clone(String_pointer string);

/**
 * Frees memory.
 */
void String_destroy(String_pointer this);

/**
 * Returns new string which will be substring of existing string.
 * Substring begins at \p begin and is \p count characters long
 * or shorter if the end of the string comes first.
 */
String_pointer String_substr(String_pointer this, size_t begin, size_t count);

/**
 * Returns true, if string \p this is empty.
 */
bool String_isEmpty(String_pointer this);

/**
 * Returns size of string \p this.
 */
size_t String_size(String_pointer this);

/**
 * Compares two strings.
 *
 * If equal, returns 0. If first is less, returns -1, otherwise returns 1.
 *
 * Shorter string is always less.
 * If strings have the same length, they are compared
 * by memcmp.
 */
int String_compare(String_pointer a, String_pointer b);

int String_compareCstr(String_pointer a, const char*);

/**
 * Returns concatenation of two strings.
 */
String_pointer String_join(String_pointer a, String_pointer b);

/**
 * Returns pointer to c string which is holding inside struct.
 * Pointer is valid as long as struct this.
 */
const char* String_toCstring(String_pointer this);

/**
 * Returns character at position \p index in string \p this.
 */
char String_at(String_pointer this, size_t index);

/**
 * Returns pointer to c_string which is holding inside string \p this.
 * Pointer is valid as long as string \p this.
 */
const char* String_data(String_pointer this);

#endif /* BETTERC_BETTER_STRING_H */
