/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#ifndef BETTERC_INPUT_STREAM_H
#define BETTERC_INPUT_STREAM_H

#include "better_string.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * Stream-like structure for reading raw data from string.
 */
struct InputStream;

typedef struct InputStream * InputStream_pointer;

/**
 * Creates stream from \p c_string, \p string or raw \p data.
 */
InputStream_pointer InputStream_fromCString(const char * c_string);
InputStream_pointer InputStream_fromString(String_pointer string);
InputStream_pointer InputStream_fromData(const char * data, size_t size);

/**
 * Frees memory.
 */
void InputStream_free(InputStream_pointer this);

/**
 * Reads or peeks single char.
 */
char InputStream_readChar(InputStream_pointer this);
char InputStream_peekChar(InputStream_pointer this);

/**
 * Reads \p size bytes into memory pointed by \p output pointer.
 */
void InputStream_readData(InputStream_pointer this, void * output, size_t size);

/**
 * Reads whole stream or at most \p count characters into string.
 */
String_pointer InputStream_readAll(InputStream_pointer this);
String_pointer InputStream_readAtMost(InputStream_pointer this, size_t count);

/**
 * Reads raw integer from stream \p this.
 */
int InputStream_readRawInt(InputStream_pointer this);

/**
 * Returns true if stream \p this has next character.
 */
bool InputStream_hasNext(InputStream_pointer this);

/**
 * Returns number of characters in stream \p this.
 */
size_t InputStream_howManyMore(InputStream_pointer this);

#endif /* BETTERC_INPUT_STREAM_H */
