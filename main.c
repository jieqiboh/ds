#include <assert.h>
#include <hashmap.h>

#include "llist.h"
#include <stdio.h>
#include "string.h"

void test_strcmp() {
    assert(strcmp("hello", "world") != 0);
    assert(strcmp("hello", "hello") == 0);
}

int main() {
    test_strcmp();

    printf("Running linked list tests...\n");
    test_llist_prepend();
    test_llist_free();
    test_llist_find();
    test_llist_delete();
    test_llist_prepend_pair();
    test_llist_find_pair();
    test_buckets();

    printf("Running hashmap tests...\n");
    test_hashmap_new();
    test_hashmap_set();
    test_hashmap_get();
    test_hashmap_delete();
    printf("All tests passed!\n");
    return 0;
}
