#include "hash_table.h"
#include "hash_funcs.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

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

typedef int (*cmp_func)(void *, void*);

typedef struct {
  void *key;
  void *value;
} pair_t;

struct hash_table {
  pair_t *data;
  ssize_t capacity;
  ssize_t elems;
  void *hashing_ctx;
  hash_func hash;
  cmp_func cmp;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_t mutex;
#endif
};

static const ssize_t initial_capacity = 7;

hash_table *create_hash_table(cmp_func cmp, ssize_t elem_size) {
  hash_table *ht = malloc(sizeof(*ht));
  ht->capacity = initial_capacity;
  ht->elems = 0;
  upm_hash_ctx *ctx = malloc(sizeof(*ctx));
  ctx->pm_ctx.prime = rand();
  ctx->pm_ctx.mult = rand();
  ctx->pm_ctx.hash_size = ht->capacity;
  ctx->off = rand();
  ht->hash = upm_hash;
  ht->cmp = cmp;
  ht->data = malloc(sizeof(*ht->data)*ht->capacity);
  return ht;
}
