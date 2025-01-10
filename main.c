#include "llist.h"
#include <stdio.h>
#include <assert.h>

// A simple comparison function for integers
bool compare_ints(const void *a, const void *b) {
    return *((int *)a) == *((int *)b);
}

// Test appending to the list
void test_llist_append() {
    llist_node node1, node2;
    int data1 = 10, data2 = 20;
    llist_init_node(&node1);
    node1.data = &data1;

    llist_init_node(&node2);
    node2.data = &data2;

    llist_node *head = NULL;
    head = llist_append(head, &node1);
    head = llist_append(head, &node2);

    // Verify the list has 2 elements and data is correct
    assert(head != NULL);  // The list should not be empty
    assert(head->data == &data1);  // First node data should be 10
    assert(head->next != NULL);  // There should be a second node
    assert(head->next->data == &data2);  // Second node data should be 20
}

// Test prepending to the list
void test_llist_prepend() {
    llist_node node1, node2;
    int data1 = 10, data2 = 20;
    llist_init_node(&node1);
    node1.data = &data1;

    llist_init_node(&node2);
    node2.data = &data2;

    llist_node *head = NULL;
    head = llist_prepend(head, &node1);
    head = llist_prepend(head, &node2);

    // Verify the list has 2 elements and data is correct
    assert(head != NULL);  // The list should not be empty
    assert(head->data == &data2);  // First node (after prepend) data should be 20
    assert(head->next != NULL);  // There should be a second node
    assert(head->next->data == &data1);  // Second node data should be 10
}

// Test finding a node in the list
void test_llist_find() {
    llist_node node1, node2;
    int data1 = 10, data2 = 20;
    llist_init_node(&node1);
    node1.data = &data1;

    llist_init_node(&node2);
    node2.data = &data2;

    llist_node *head = NULL;
    head = llist_append(head, &node1);
    head = llist_append(head, &node2);

    llist_node *found_node = llist_find(head, &data2, compare_ints);
    assert(found_node != NULL);  // The node should be found
    assert(found_node->data == &data2);  // The found node's data should be 20
}

// Test deleting a node in the list
void test_llist_delete() {
    llist_node node1, node2, node3;
    int data1 = 10, data2 = 20, data3 = 30;
    llist_init_node(&node1);
    node1.data = &data1;

    llist_init_node(&node2);
    node2.data = &data2;

    llist_init_node(&node3);
    node3.data = &data3;

    llist_node *head = NULL;
    head = llist_append(head, &node1);
    head = llist_append(head, &node2);
    head = llist_append(head, &node3);

    llist_delete(&head, &node2);
    assert(head->data == &data1);
    assert(head->next->data == &data3);

    llist_delete(&head, &node1);
    assert(head->data == &data3);

    llist_delete(&head, &node3);
    assert(llist_is_empty(head) == true);  // llist should be empty now
}

// Test if the list is empty
void test_llist_is_empty() {
    llist_node *head = NULL;

    assert(llist_is_empty(head) == true);  // Empty list, should return true

    int data = 10;
    llist_node node;
    llist_init_node(&node);
    node.data = &data;

    head = llist_append(head, &node);

    assert(llist_is_empty(head) == false);  // List with one element, should return false
}

int main() {
    printf("Running linked list tests...\n");

    test_llist_append();
    test_llist_prepend();
    test_llist_find();
    test_llist_delete();
    test_llist_is_empty();

    printf("All tests passed!\n");
    return 0;
}
