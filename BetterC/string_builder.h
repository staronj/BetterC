/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#ifndef BETTERC_STRING_BUILDER_H
#define BETTERC_STRING_BUILDER_H

#include "better_string.h"

struct StringBuilder;

typedef struct StringBuilder * StringBuilder_pointer;

/**
 * Creates new empty string builder
 */
StringBuilder_pointer StringBuilder_createEmpty();

/**
 * Creates StringBuilder from string.
 */
StringBuilder_pointer StringBuilder_fromString(String_pointer string);

/**
 * Creates StringBuilder from data.
 */
StringBuilder_pointer StringBuilder_fromData(const char * data, size_t size);

/**
 * Creates StringBuilder from c string.
 */
StringBuilder_pointer StringBuilder_fromCString(const char * c_string);

/**
 * Frees memory.
 */
void StringBuilder_free(StringBuilder_pointer this);

/**
 * Reserves more memory for performance purposes.
 */
void StringBuilder_reserve(StringBuilder_pointer this, size_t target_capacity);

/**
 * Clears StringBuilder.
 * Note that it will not free or shrink allocated memory.
 */
void StringBuilder_clear(StringBuilder_pointer this);

/**
 * Creates new String from StringBuilder.
 */
String_pointer StringBuilder_toString(StringBuilder_pointer this);

/**
 * Appends character, c_string, raw data or string at the end of \p this.
 */
void StringBuilder_appendChar(StringBuilder_pointer this, char c);
void StringBuilder_appendCString(StringBuilder_pointer this, const char * c_string);
void StringBuilder_appendData(StringBuilder_pointer this, const char * data, size_t size);
void StringBuilder_appendString(StringBuilder_pointer this, String_pointer string);

/**
 * Appends raw od formatted string at the end of \p this.
 */
void StringBuilder_appendRawInt(StringBuilder_pointer this, int n);
void StringBuilder_appendFormattedInt(StringBuilder_pointer this, int n);

/**
 * Inserts character, c_string, raw data or string at position \p position of \p this.
 */
void StringBuilder_insertChar(StringBuilder_pointer this, size_t position, char c);
void StringBuilder_insertCString(StringBuilder_pointer this, size_t position, const char * c_string);
void StringBuilder_insertData(StringBuilder_pointer this, size_t position, const char * data, size_t size);
void StringBuilder_insertString(StringBuilder_pointer this, size_t position, String_pointer string);

/**
 * Returns pointer to internal StringBuilder data pointer.
 * You can use it for changing individual characters.
 * Note that call of any function of StringBuilder invalidates this pointer!
 */
char * StringBuilder_data(StringBuilder_pointer this);

/**
 * Returns size of string builder \p this.
 */
size_t StringBuilder_size(StringBuilder_pointer this);

/**
 * Returns true, if string builder \p this is empty.
 */
bool StringBuilder_empty(StringBuilder_pointer this);

#endif /* BETTERC_STRING_BUILDER_H */
