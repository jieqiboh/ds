#ifndef STRING_H
#define STRING_H

#include <stddef.h>

int memcmp(const void *, const void *, size_t);
void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
void *memchr(const void *, int, size_t);
size_t strlen(const char *);
int strcmp(const void *a, const void *b);

#endif
