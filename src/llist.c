#include "llist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

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
llist_node *llist_find(llist_node *head, void *data, llist_compare_fn cmp) {
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
void llist_delete(llist_node **head, void *data, llist_compare_fn cmp) {
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

// Tests
// A simple comparison function for pairs
bool compare_ints(const void *a, const void *b) {
    return *((int *)a) == *((int *)b);
}

// Test appending to the list
void test_llist_prepend() {
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    llist_node *head = llist_new(&data3, sizeof(data3));;
    head = llist_prepend(head, &data1, sizeof(data1));
    head = llist_prepend(head, &data2, sizeof(data2));

    // data order: 2 1 3
    assert(head != NULL);  // The list should not be empty
    assert(*(int *)head->data == data2);  // First node data should be 20
    assert(head->next != NULL);  // There should be a second node

    assert(*(int *)head->next->data == data1);  // Second node data should be 10
    assert(head->next != NULL);  // There should be a second node

    assert(*(int *)head->next->next->data == data3);  // Third node data should be 30

    llist_free(head);
}

// Test appending to the list
void test_llist_free() {
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    llist_node *head = llist_new(&data3, sizeof(data3));;
    head = llist_prepend(head, &data1, sizeof(data1));
    head = llist_prepend(head, &data2, sizeof(data2));

    llist_free(head);
    head = NULL;
    assert(head == NULL);

    head = NULL;
    llist_free(head);
    assert(head == NULL);
}

// Test llist find
void test_llist_find() {
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    llist_node *head = llist_new(&data3, sizeof(data3));;
    head = llist_prepend(head, &data1, sizeof(data1));
    head = llist_prepend(head, &data2, sizeof(data2));

    // data order: 2 1 3
    assert(head != NULL);  // The list should not be empty
    assert(*(int *)head->data == data2);  // First node data should be 20
    assert(head->next != NULL);  // There should be a second node

    assert(*(int *)head->next->data == data1);  // Second node data should be 10
    assert(head->next != NULL);  // There should be a second node

    assert(*(int *)head->next->next->data == data3);  // Third node data should be 30

    llist_node *found_node = llist_find(head, &data2, compare_ints);
    assert(found_node != NULL);
    assert(*(int *)found_node->data == 20);

    found_node = llist_find(head, &data3, compare_ints);
    assert(found_node != NULL);
    assert(*(int *)found_node->data == 30);

    found_node = llist_find(head, &data1, compare_ints);
    assert(found_node != NULL);
    assert(*(int *)found_node->data == 10);

    llist_free(head);
}

// Test llist delete
void test_llist_delete() {
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    llist_node *head = llist_new(&data3, sizeof(data3));;
    head = llist_prepend(head, &data1, sizeof(data1));
    head = llist_prepend(head, &data2, sizeof(data2));

    // data order: 2 1 3
    assert(head != NULL);  // The list should not be empty
    assert(*(int *)head->data == data2);  // First node data should be 20
    assert(head->next != NULL);  // There should be a second node

    assert(*(int *)head->next->data == data1);  // Second node data should be 10
    assert(head->next != NULL);  // There should be a second node

    assert(*(int *)head->next->next->data == data3);  // Third node data should be 30

    llist_delete(NULL, &data1, compare_ints); // should work without any errors

    assert(*(int *)llist_find(head, &data1, compare_ints)->data == 10);
    assert(*(int *)llist_find(head, &data2, compare_ints)->data == 20);
    assert(*(int *)llist_find(head, &data3, compare_ints)->data == 30);

    llist_delete(&head, &data1, compare_ints);
    assert(llist_find(head, &data1, compare_ints) == NULL);

    llist_delete(&head, &data2, compare_ints);
    assert(llist_find(head, &data2, compare_ints) == NULL);

    llist_delete(&head, &data3, compare_ints);
    assert(llist_find(head, &data3, compare_ints) == NULL);

    llist_free(head);
}

// A simple comparison function for pairs
bool compare_pairs(const void *a, const void *b) {
    return strcmp(((pair *)a)->key, ((pair *)b)->key) == 0;
}

// Test appending pairs to the list
void test_llist_prepend_pair() {
    pair pair1 = { .key = "hello", .value = &(int){100} };
    pair pair2 = { .key = "world", .value = &(int){200} };
    pair pair3 = { .key = "pair3", .value = &(int){300} };

    llist_node *head = llist_new(&pair1, sizeof(pair1));;
    head = llist_prepend(head, &pair2, sizeof(pair2));
    head = llist_prepend(head, &pair3, sizeof(pair3));

    // data order: 3 2 1
    assert(head != NULL);  // The list should not be empty

    // check pair3
    assert(strcmp(((pair *)(head->data))->key, "pair3") == 0);
    assert(*(int *)((pair *)head->data)->value == 300);

    // check pair2
    assert(strcmp(((pair *)(head->next->data))->key, "world") == 0);
    assert(*(int *)((pair *)head->next->data)->value == 200);

    // check pair1
    assert(strcmp(((pair *)(head->next->next->data))->key, "hello") == 0);
    assert(*(int *)((pair *)head->next->next->data)->value == 100);
    llist_free(head);
}

// Test finding a pair in the llist
void test_llist_find_pair() {
    pair pair1 = { .key = "hello", .value = &(int){100} };
    pair pair2 = { .key = "world", .value = &(int){200} };
    pair pair3 = { .key = "pair3", .value = &(int){300} };
    pair pair4 = { .key = "pair4", .value = &(int){0} };

    llist_node *head = llist_new(&pair1, sizeof(pair1));;
    head = llist_prepend(head, &pair2, sizeof(pair2));
    head = llist_prepend(head, &pair3, sizeof(pair3));

    // data order: 3 2 1
    assert(head != NULL);  // The list should not be empty

    // find pair1
    llist_node *found_node = llist_find(head, &pair1, compare_pairs);
    assert(strcmp(((pair *)(found_node->data))->key, "hello") == 0);
    assert(*(int *)((pair *)(found_node->data))->value == 100);

    // find pair2
    found_node = llist_find(head, &pair2, compare_pairs);
    assert(strcmp(((pair *)(found_node->data))->key, "world") == 0);
    assert(*(int *)((pair *)(found_node->data))->value == 200);

    // find pair3
    found_node = llist_find(head, &pair3, compare_pairs);
    assert(strcmp(((pair *)(found_node->data))->key, "pair3") == 0);
    assert(*(int *)((pair *)(found_node->data))->value == 300);

    //find a node that doesn't exist
    found_node = llist_find(head, &pair4, compare_pairs);
    assert(found_node == NULL);

    llist_free(head);
}

void test_buckets() {
    pair pair1 = { .key = "world", .value = &(int){200} };

    int cap = 64;
    int idx = 47;
    llist_node **buckets = (llist_node **)malloc(cap * sizeof(llist_node *));
    buckets[idx] = llist_prepend(buckets[idx], &pair1, sizeof(pair));

    // llist_node *head = llist_new(&pair1, sizeof(pair1));;
    llist_node *head = buckets[idx];
    // Access the pair structure from the node's data
    pair *p = (pair *)head->data;  // Cast to pair pointer

    // printf("Key: %s\n", (char *)p->key);
    // Print the key (which is a string)
    assert(strcmp((char *)p->key, pair1.key) == 0);

    for (int i = 0; i < cap; i++) {
        llist_free(buckets[i]);
    }
    free(buckets);
}
