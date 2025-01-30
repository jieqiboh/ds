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

    return (pair *)llist_find(head, p, map->cmp)->data;
}


// hashmap_set inserts or replaces a value in the hash map.
// This operation may allocate memory.
void hashmap_set(hashmap *map, pair *p) {
    uint64_t llist_idx = map->hash(p) % map->cap;

    // Prepend the new node
    map->buckets[llist_idx] = llist_prepend(map->buckets[llist_idx], p, sizeof(pair));
}

// hashmap_delete removes an item from the hash map and returns it. If the
// item is not found then NULL is returned.
void *hashmap_delete(hashmap *map, pair *p) {
    return NULL;
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

    pair pair1 = { .key = "helloworld", .value = &(int){53} };
    hashmap_set(map, &pair1);

    // find pair1
    pair *found_pair = hashmap_get(map, &pair1);
    assert(strcmp((char *)found_pair->key, "helloworld") == 0);

    hashmap_free(map);
}

void test_hashmap_get() {

}

void test_hashmap_free() {
}

void test_hashmap_delete() {

}
