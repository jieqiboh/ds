#include "llist.h"

// Append a node to the end of the list.
llist_node *llist_append(llist_node *head, llist_node *node) {
    if (head == NULL) {
        return node; // If the list is empty, the new node becomes the head
    }

    llist_node *cur = head;
    while (cur->next != NULL) {
        cur = cur->next; // Traverse to the end of the list
    }
    cur->next = node; // Link the new node
    node->next = NULL; // Ensure the appended node's next is NULL
    return head;
}

// Prepend a node to the beginning of the list.
llist_node *llist_prepend(llist_node *head, llist_node *node) {
    node->next = head; // Make the new node point to the current head
    return node;       // The new node becomes the head
}

// Delete a node from the list.
void llist_delete(llist_node **head, llist_node *node) {
    if (head == NULL || *head == NULL || node == NULL) {
        return; // Do nothing if the list or node is NULL
    }

    llist_node *cur = *head;
    llist_node *prev = NULL;

    while (cur != NULL) {
        if (cur == node) {
            if (prev == NULL) {
                // Head node case: the node to delete is the head
                *head = cur->next;
            } else {
                // Bypass the current node
                prev->next = cur->next;
            }
            node->next = NULL; // Ensure the deleted node is isolated
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}


// Find a node matching data.
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

