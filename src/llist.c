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
