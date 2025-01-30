#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>
#include <stdbool.h>

// Define the function signature for the equality check
typedef bool (*llist_compare_fn)(const void *a, const void *b);

// // Define the function signature for freeing malloc'ed data
// typedef void (*llist_free_data_fn)(void *data);

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

// Find a node in the linked list using the compare function
llist_node *llist_find(llist_node *head, void *data, llist_compare_fn cmp);

// Delete a node in the linked list found using the compare function
void llist_delete(llist_node **head, void *data, llist_compare_fn cmp);

// Tests
void test_llist_prepend();
void test_llist_free();
void test_llist_find();
void test_llist_delete();
void test_llist_prepend_pair();
void test_llist_find_pair();
void test_buckets();
#endif



