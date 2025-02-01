#include <stddef.h>

// memcmp returns 0 if s1 and s2 are equal, 1 otherwise
int memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *a = s1;
	const unsigned char *b = s2;
	for (size_t i = 0; i < n; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}

// memcpy copies n bytes from the memory area pointed to by s2 to the memory area pointed to by s1.
// The memory areas must not overlap. For overlapping memory areas, use memmove instead.
// Returns a pointer to the destination memory area s1.
void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
	unsigned char *dst = s1;
	const unsigned char *src = s2;
	for (size_t i = 0; i < n; i++)
		dst[i] = src[i];
	return s1;
}

// memmove copies n bytes from the memory area pointed to by s2 to the memory area pointed to by s1.
// Unlike memcpy, memmove handles overlapping memory areas safely by copying bytes in the correct order.
// Returns a pointer to the destination memory area s1.
void *memmove(void *s1, const void *s2, size_t n)
{
	unsigned char *dst = s1;
	const unsigned char *src = s2;
	if (s1 < s2) {
		for (size_t i = 0; i < n; i++)
			dst[i] = src[i];
	} else {
		for (size_t i = n; i > 0; i--)
			dst[i - 1] = src[i - 1];
	}
	return s1;
}

// memset fills the first n bytes of the memory area pointed to by s with the constant byte c.
// Returns a pointer to the memory area s.
void *memset(void *s, int c, size_t n)
{
	unsigned char *p = s, *end = p + n;
	for (; p != end; p++) {
		*p = (unsigned char)c;
	}
	return s;
}

// memchr scans the first n bytes of the memory area pointed to by s for the first occurrence of the byte c.
// Returns a pointer to the matching byte, or NULL if the byte is not found.
void *memchr(const void *s, int c, size_t n)
{
	const unsigned char *p = (const unsigned char *)s;
	while (n-- > 0) {
		if (*p == (unsigned char)c)
			return (void *)p;
		else
			p++;
	}
	return NULL;
}

// strlen computes the length of the null-terminated string pointed to by s.
// The length is the number of characters before the null terminator ('\0').
// Returns the length of the string.
size_t strlen(const char *s)
{
	size_t len = 0;
	while (*s++)
		len++;
	return len;
}

int strcmp(const void *a, const void *b) {
	const char *str1 = *(const char **)a;
	const char *str2 = *(const char **)b;

	// Use memcmp to compare the two strings, including the null terminator
	return memcmp(str1, str2, strlen(str1) + 1) == 0;
}