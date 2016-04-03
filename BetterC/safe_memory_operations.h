/**
 * Copyright Jakub Staroń 2015 - 2016
 */

#ifndef BETTERC_SAFE_MEMORY_OPERATIONS_H
#define BETTERC_SAFE_MEMORY_OPERATIONS_H

#include <stddef.h>
#include <malloc.h>

/**
 * Copies memory from source to destination.
 * If memory blocks can overlap, use move instead.
 */
void safe_raw_copy(void* destination, const void* source, size_t number, size_t sizeOfElement);

/**
 * Allocates memory and fill it with zeros.
 */
void* safe_raw_allocate(size_t number, size_t sizeOfElement);

/**
 * Increments void pointer by \p offset of \p elementSize bytes.
 */
void* safe_raw_offset(void* pointer, ptrdiff_t offset, size_t elementSize);

/**
 * Moves memory. Can be slower than copy.
 */
void safe_raw_move(void* data, size_t size, ptrdiff_t offset, size_t elementSize);

/**
 * Copies table of characters.
 */
void safe_char_copy(char* destination, const char* source, size_t number);

/**
 * Allocates table of characters.
 */
char* safe_char_allocate(size_t number);

/**
 * Moves table of characters.
 */
void safe_char_move(char* data, size_t size, ptrdiff_t offset);

/**
 * Fills memory pointed by \p pointer with zeros.
 */
void safe_zero_memory(void* pointer, size_t number, size_t sizeOfElement);

#endif /* BETTERC_SAFE_MEMORY_OPERATIONS_H */