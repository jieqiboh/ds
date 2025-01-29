#include "llist.h"
#include <stdio.h>
#include <assert.h>

// A simple comparison function for integers
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

int main() {
    printf("Running linked list tests...\n");

    test_llist_prepend();
    test_llist_free();
    test_llist_find();

    printf("All tests passed!\n");
    return 0;
}
