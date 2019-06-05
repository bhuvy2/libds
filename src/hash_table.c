#include "hash_table.h"
#include "hash_funcs.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef LIBDS_PTHREAD_ENABLED
#include <pthread.h>
#endif

static const ssize_t ht_capacities[] = {
                                      7,
                                      31,
                                      127,
                                      8191,
                                      131071,
                                      524287,
                                      2147483647
};

static const ssize_t candidate_primes[] = {
                                           7,
                                           31,
                                           127,
                                           8191,
                                           131071,
                                           524287,
                                           2147483647,
                                           2305843009213693951L,
};

typedef struct {
  void *key;
  void *value;
} pair_t;

struct hash_table {
  ssize_t capacity;
  ssize_t elems;
  ssize_t elem_size;
  hash_func hash;
  cmp_func cmp;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_t mutex;
#endif
  ssize_t hashing_ctx_size;
  char hashing_ctx[0];
  // After the hashing ctx is the bitmap
  // Then are the elements
};

typedef unsigned char* bitmap;

static ssize_t bitmap_size(ssize_t elems) {
  return (elems + 7) / 8;
}

void set_bitmap(bitmap b, int i) {
  b[i / 8] |= 1 << (i & 7);
}

void unset_bitmap(bitmap b, int i) {
  b[i / 8] &= ~(1 << (i & 7));
}

int get_bitmap(bitmap b, int i) {
  return b[i / 8] & (1 << (i & 7)) ? 1 : 0;
}

static pair_t *get_pairs(hash_table *ht) {
  return (pair_t*)(ht->hashing_ctx + ht->hashing_ctx_size + bitmap_size(ht->capacity));
}

static bitmap get_bitmap_ht(hash_table *ht) {
  return (bitmap)(ht->hashing_ctx + ht->hashing_ctx_size);
}


static ssize_t call_hash(hash_table *ht, const char *data) {
  if (ht->elem_size <= 0) {
    return ht->hash(&data, sizeof(data), (void *)ht->hashing_ctx);
  }
  return ht->hash(data, ht->elem_size, (void *)ht->hashing_ctx);
}

static const ssize_t initial_capacity = 7;

hash_table *__hash_table_from_capacity(cmp_func cmp, ssize_t elem_size, ssize_t capacity) {
  ssize_t initial_size = sizeof(pair_t *)*capacity;
  ssize_t bmap_size = bitmap_size(capacity);
  hash_table *ht = malloc(sizeof(*ht) +
                          sizeof(upm_hash_ctx) +
                          bmap_size +
                          initial_size);
  upm_hash_ctx *ctx = (upm_hash_ctx *) ht->hashing_ctx;

  ht->capacity = capacity;
  ht->elems = 0;
  ht->elem_size = elem_size;
  ctx->pm_ctx.prime = candidate_primes[1];
  ctx->pm_ctx.mult = rand();
  ctx->pm_ctx.hash_size = ht->capacity;
  ctx->off = rand();
  ht->hash = upm_hash;
  ht->cmp = cmp;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_init(&ht->mutex, NULL);
#endif
  ht->hashing_ctx_size = sizeof(*ctx);

  memset(((char *)ht) + sizeof(*ht) + sizeof(upm_hash_ctx), 0, bmap_size);
  return ht;
}

hash_table *ht_create(cmp_func cmp, ssize_t elem_size) {
  return __hash_table_from_capacity(cmp, elem_size, initial_capacity);
}

hash_table *ht_from_reserved_size(cmp_func cmp, ssize_t elem_size, ssize_t almost_capacity) {
  ssize_t cap = ht_capacities[0];
  for (int i = 1; i < sizeof(ht_capacities) / sizeof(ht_capacities[0]) && cap < almost_capacity; ++i) {
    cap = ht_capacities[i];
  }

  return __hash_table_from_capacity(cmp, elem_size, cap);
}



static ssize_t __get_hash_index(hash_table *ht, void *key) {
  pair_t *pairs = get_pairs(ht);
  ssize_t hash = call_hash(ht, key) % ht->capacity;
  bitmap mp = get_bitmap_ht(ht);

  // Check if we have a quick hit
  if (get_bitmap(mp, hash) == 0 || ht->cmp(key, pairs[hash].key) == 0) {
    return hash;
  }

  for (ssize_t probe = (hash + 1) % ht->capacity; probe != hash; probe = (probe + 1) % ht->capacity) {
    if (get_bitmap(mp, probe) == 0 || ht->cmp(key, pairs[probe].key) == 0) {
      return probe;
    }
  }
  return -1;
}

int ht_set(hash_table *ht, void *key, void *val) {
  ssize_t idx = __get_hash_index(ht, key);
  if (idx == -1) {
    return 1;
  }

  bitmap mp = get_bitmap_ht(ht);
  pair_t *pairs = get_pairs(ht);
  set_bitmap(mp, idx);
  pairs[idx].value = val;
  pairs[idx].key = key;
  return 0;
}

int ht_get(hash_table *ht, void *key, void **val) {
  pair_t *pairs = get_pairs(ht);
  ssize_t hash = call_hash(ht, key) % ht->capacity;
  bitmap mp = get_bitmap_ht(ht);

  // Check if we have a quick hit
  if (get_bitmap(mp, hash) == 1 && ht->cmp(key, pairs[hash].key) == 0) {
    *val = pairs[hash].value;
    return 0;
  }

  for (ssize_t probe = (hash + 1) % ht->capacity; probe != hash; probe = (probe + 1) % ht->capacity) {
    if (get_bitmap(mp, probe) == 1 && ht->cmp(key, pairs[probe].key) == 0) {
      *val = pairs[probe].value;
      return 0;
    }
  }
  return 1;
}

int ht_clear(hash_table *ht) {
  ssize_t bmap_size = bitmap_size(ht->capacity);
  memset(((char *)ht) + sizeof(*ht) + sizeof(upm_hash_ctx), 0, bmap_size);
}

int ht_delete(hash_table *ht, void *key) {
  ssize_t idx = __get_hash_index(ht, key);
  if (idx == -1) {
    return 1;
  }

  bitmap mp = get_bitmap_ht(ht);
  unset_bitmap(mp, idx);
  // TODO: Decrease size
  return 0;
}

int ht_delete_if(hash_table *ht, int (*key_cmp)(void*)) {
  pair_t *pairs = get_pairs(ht);
  bitmap mp = get_bitmap_ht(ht);
  for (ssize_t probe = 0; probe < ht->capacity; probe++) {
    if (get_bitmap(mp, probe) == 1 && key_cmp(pairs[probe].key)) {
      unset_bitmap(mp, probe);
    }
  }
  return 0;
}

int ht_keys(hash_table *ht, vector **keys) {
  abort();
}

int ht_values(hash_table *ht, vector **values) {
  abort();
}

ssize_t ht_size(hash_table *ht) {
  abort();
}

hash_table *ht_merge(const hash_table *ht1, const hash_table *ht2) {
  abort();
}

void ht_rehash(hash_table *ht) {
  abort();
}

hash_table *ht_filter(const hash_table *ht, int (*cmp)(void*, void*)) {
  abort();
}

