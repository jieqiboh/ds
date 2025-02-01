#ifndef HASHMAP_H
#define HASHMAP_H

#include "llist.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct pair {
  void *key;
  void *value;
} pair;

typedef struct hashmap {
  size_t cap;                         // Capacity of hashmap
  uint64_t (*hash)(pair *p);        // Hash function operates on key
  llist_compare_fn cmp;               // llist comparison function for hashmap keys
  llist_node **buckets;              // Flexible array member for chaining
} hashmap;

hashmap *hashmap_new(size_t cap, uint64_t (*hash)(pair *p), llist_compare_fn);

void hashmap_free(hashmap *map);

// Finds the corresponding value if this pair's key exists in the hashmap
pair *hashmap_get(hashmap *map, pair *p);

// Sets the key-value pair in the hashmap, overwriting previous values if they exist
void hashmap_set(hashmap *map, pair *p);

// Deletes the key-value pair from the hashmap if it exists, given the pair
void *hashmap_delete(hashmap *map, pair *p);

// Tests
void test_hashmap_new();
void test_hashmap_set();
void test_hashmap_get();
#endif
