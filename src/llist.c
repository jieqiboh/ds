#include "llist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Will need to change malloc to kalloc in kernel dev
llist_node *llist_new(void *data, size_t data_size) {
    llist_node *newNode = (llist_node *)malloc(sizeof(llist_node));

    newNode->data = malloc(data_size);
    newNode->next = NULL;

    memcpy(newNode->data, data, data_size);

    return newNode;
}

// Prepend a node to the beginning of the list.
llist_node *llist_prepend(llist_node *head, void *data, size_t data_size) {
    llist_node *newNode = llist_new(data, data_size);
    newNode->next = head; // Make the new node point to the current head
    return newNode;       // The new node becomes the head
}

// Frees an entire linked list
void llist_free(llist_node* head) {
    llist_node *cur = head;
    llist_node *nxt;
    
    while (cur != NULL) {
        nxt = cur->next;
        free(cur->data);
        free(cur);
        cur = nxt;
    }
}

// Find a node matching data using a comparison function
llist_node *llist_find(llist_node *head, void *data, llist_compare_func cmp) {
    llist_node *cur = head;
    while (cur != NULL) {
        if (cmp(cur->data, data)) { // Use the custom comparison function
            return cur; // Return the node if the data matches
        }
        cur = cur->next; // Move to the next node
    }
    return NULL; // Return NULL if no match is found
}

// Delete a node from the linked list, found matching data by the list_compare_function
void llist_delete(llist_node **head, void *data, llist_compare_func cmp) {
    if (head == NULL || *head == NULL) {
        return; // Do nothing if the list or node is NULL
    }

    llist_node *cur = *head;
    llist_node *prev = NULL;

    while (cur != NULL) {
        if (cmp(cur->data, data)) {
            if (prev == NULL) {
                // Head node case: the node to delete is the head
                *head = cur->next;
            } else {
                // Bypass the current node
                prev->next = cur->next;
            }
            free(cur->data); // free the current node
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
