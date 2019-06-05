#pragma once

#include <vector.h>

struct hash_table;

typedef struct hash_table hash_table;

typedef int (*cmp_func)(void *, void*);

hash_table *ht_create(cmp_func cmp, ssize_t elem_size);

hash_table *ht_from_reserved_size(cmp_func cmp, ssize_t elem_size, ssize_t almost_capacity);

int ht_set(hash_table *ht, void *key, void *val);

int ht_get(hash_table *ht, void *key, void **val);

int ht_clear(hash_table *ht);

int ht_delete(hash_table *ht, void *key);

int ht_delete_if(hash_table *ht, int (*key_cmp)(void*));

int ht_keys(hash_table *ht, vector **keys);

int ht_values(hash_table *ht, vector **values);

ssize_t ht_size(hash_table *ht);

hash_table *ht_merge(const hash_table *ht1, const hash_table *ht2);

void ht_rehash(hash_table *ht);

hash_table *ht_filter(const hash_table *ht, int (*cmp)(void*, void*));
