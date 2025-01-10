#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct llist_node {
	void *data;
	struct llist_node *next;
} llist_node;

// no malloc involved, assume memory is guaranteed

// Initialize a linked list node.
static inline void llist_init_node(llist_node *node) {
    node->next = NULL;
}

// Check if a linked list is empty.
static inline bool llist_is_empty(const llist_node *head) {
    return head == NULL;
}

// Append a node to the end of the list.
llist_node *llist_append(llist_node *head, llist_node *node);

// Prepend a node to the beginning of the list.
llist_node *llist_prepend(llist_node *head, llist_node *node);

// Delete a node from the list
void llist_delete(llist_node **head, llist_node *node);

// Define the function signature for the equality check
typedef bool (*llist_compare_func)(const void *a, const void *b);

// Find a node matching data
llist_node *llist_find(llist_node* head, void* data, llist_compare_func);

#endif



