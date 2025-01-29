#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct llist_node {
	void *data;
	struct llist_node *next;
} llist_node;

// Initialise a new linked list node.
llist_node *llist_new(void *data, size_t data_size);

// Prepend a new node to the beginning of the list.
llist_node *llist_prepend(llist_node *head, void *data, size_t data_size);

// Free an entire linked list
void llist_free(llist_node *node);

// Define the function signature for the equality check
typedef bool (*llist_compare_func)(const void *a, const void *b);

// Find a node in the linked list using the compare function
llist_node *llist_find(llist_node* head, void* data, llist_compare_func);

#endif



