#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "hashmap.h"
#include <assert.h>
#include <stdio.h>

#include "llist.h"
#include "string.h"

// hashmap_new initialises and returns a hash map. 
// The hashmap comprises an array of linked lists, and each node in the linked list contains a key-value pair
// Param `cap` is the default lower capacity of the hashmap. Setting this to
// zero will default to 16.
// Param `hash` is a function that generates a hash value for a given key.
hashmap *hashmap_new(size_t cap, uint64_t (*hash)(pair *p), llist_compare_fn cmp) {
    size_t ncap = 16;
    cap = (cap < ncap) ? ncap : cap;

    hashmap *map = (hashmap *)malloc(sizeof(hashmap));
    map->cap = (cap < ncap) ? ncap : cap;
    map->hash = hash;
    map->cmp = cmp;
    map->buckets = (llist_node **)malloc(cap * sizeof(llist_node *));
    // Initialize buckets with simple integer data wrapped in llist_node
    for (size_t i = 0; i < map->cap; i++) {
        map->buckets[i] = NULL;
    }
    return map;
}

// hashmap_free frees the hash map completely
// Every llist in the hashmap is freed
void hashmap_free(hashmap *map) {
    for (size_t i = 0; i < map->cap; i++) {
        llist_free(map->buckets[i]);
    }
    free(map->buckets);  // Free the dynamically allocated bucket array
    free(map);
}

// hashmap_get returns the value based on the provided key. If the item is not
// found then NULL is returned.
pair *hashmap_get(hashmap *map, pair *p) {
    uint64_t llist_idx = map->hash(p) % map->cap;
    llist_node *head = map->buckets[llist_idx];

    llist_node *found_node = llist_find(head, p, map->cmp);
    if (found_node == NULL) {
        return NULL;
    }
    return (pair *)llist_find(head, p, map->cmp)->data;
}


// hashmap_set inserts or replaces a value in the hash map.
// This operation may allocate memory.
void hashmap_set(hashmap *map, pair *p) {
    uint64_t llist_idx = map->hash(p) % map->cap;

    // Prepend the new node
    map->buckets[llist_idx] = llist_prepend(map->buckets[llist_idx], p, sizeof(pair));
}

// hashmap_delete removes an item from the hash map.
void hashmap_delete(hashmap *map, pair *p) {
    uint64_t llist_idx = map->hash(p) % map->cap;

    llist_delete(&map->buckets[llist_idx], p, map->cmp);
}

// Tests
uint64_t hash_string(void *item) {
    char *str = (char *)item;
    uint64_t hash = 0;

    while (*str) {
        hash += (uint64_t)(*str);
        str++;
    }

    return hash;
}

bool hashmap_compare_pairs(const void *a, const void *b) {
    pair *pair_a = (pair *)a;
    pair *pair_b = (pair *)b;
    return strcmp(pair_a->key, pair_b->key) == 0;
}

void test_hashmap_new() {
    hashmap *map = hashmap_new(64, hash_string, hashmap_compare_pairs);

    assert(map->cap == 64);
    for (int i = 0; i < map->cap; i++) {
        assert(map->buckets[i] == NULL);
    }

    hashmap_free(map);
}

void test_hashmap_set() {
    // create a hashmap that maps strings to numbers
    hashmap *map = hashmap_new(64, hash_string, hashmap_compare_pairs);

    pair pair1 = { .key = "helloworld", .value = &(int){123} };
    hashmap_set(map, &pair1);

    pair pair2 = { .key = "pair2", .value = &(int){321} };
    hashmap_set(map, &pair2);

    pair pair3 = { .key = "pair3", .value = &(int){456} };
    hashmap_set(map, &pair3);

    // find pair1
    pair *found_pair = hashmap_get(map, &pair1);
    assert(strcmp((char *)found_pair->key, "helloworld") == 0);
    assert(*(int *)found_pair->value == 123);

    // find pair2
    found_pair = hashmap_get(map, &pair2);
    assert(strcmp((char *)found_pair->key, "pair2") == 0);
    assert(*(int *)found_pair->value == 321);

    // find pair3
    found_pair = hashmap_get(map, &pair3);
    assert(strcmp((char *)found_pair->key, "pair3") == 0);
    assert(*(int *)found_pair->value == 456);
    hashmap_free(map);
}

void test_hashmap_get() {
    // create a hashmap that maps strings to numbers
    hashmap *map = hashmap_new(64, hash_string, hashmap_compare_pairs);

    pair pair1 = { .key = "helloworld", .value = &(int){123} };
    hashmap_set(map, &pair1);

    pair pair2 = { .key = "helloworld", .value = &(int){321} };
    hashmap_set(map, &pair2);

    pair pair3 = { .key = "pair3", .value = &(int){456} };
    hashmap_set(map, &pair3);

    pair pair4 = { .key = "pair4", .value = &(int){0} };

    // find pair1
    pair *found_pair = hashmap_get(map, &pair1);
    assert(strcmp((char *)found_pair->key, "helloworld") == 0);
    assert(*(int *)found_pair->value == 321);

    // find pair2 which should have overwritten pair1's key
    found_pair = hashmap_get(map, &pair2);
    assert(strcmp((char *)found_pair->key, "helloworld") == 0);
    assert(*(int *)found_pair->value == 321);

    found_pair = hashmap_get(map, &pair3);
    assert(strcmp((char *)found_pair->key, "pair3") == 0);
    assert(*(int *)found_pair->value == 456);

    // find pair4
    found_pair = hashmap_get(map, &pair4);
    assert(found_pair == NULL);

    hashmap_free(map);
}

void test_hashmap_delete() {
    // create a hashmap that maps strings to numbers
    hashmap *map = hashmap_new(64, hash_string, hashmap_compare_pairs);

    pair pair1 = { .key = "abc", .value = &(int){123} };
    hashmap_set(map, &pair1);

    pair pair2 = { .key = "bac", .value = &(int){321} };
    hashmap_set(map, &pair2);

    pair pair3 = { .key = "xyz", .value = &(int){456} };
    hashmap_set(map, &pair3);

    pair pair4 = { .key = "yxz", .value = &(int){456} };
    hashmap_set(map, &pair4);

    hashmap_delete(map, &pair1);
    hashmap_delete(map, &pair4);

    // find pair1
    pair *found_pair = hashmap_get(map, &pair1);
    assert(found_pair == NULL);

    // find pair2
    found_pair = hashmap_get(map, &pair2);
    assert(strcmp((char *)found_pair->key, "bac") == 0);
    assert(*(int *)found_pair->value == 321);

    // find pair3
    found_pair = hashmap_get(map, &pair3);
    assert(strcmp((char *)found_pair->key, "xyz") == 0);
    assert(*(int *)found_pair->value == 456);

    // find pair4
    found_pair = hashmap_get(map, &pair4);
    assert(found_pair == NULL);

    // delete pair2 and pair3
    hashmap_delete(map, &pair2);
    hashmap_delete(map, &pair3);

    // find pair2 and pair3, which should be missing
    found_pair = hashmap_get(map, &pair2);
    assert(found_pair == NULL);

    found_pair = hashmap_get(map, &pair3);
    assert(found_pair == NULL);

    hashmap_free(map);
}
