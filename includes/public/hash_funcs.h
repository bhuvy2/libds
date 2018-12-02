#pragma once
#include <stdlib.h>

typedef ssize_t (*hash_func)(const void *, ssize_t, void*);

struct pm_hash_ctx {
  ssize_t prime;
  ssize_t mult;
  ssize_t hash_size;
};
typedef struct pm_hash_ctx pm_hash_ctx;

ssize_t pm_hash(const void* data, ssize_t size, pm_hash_ctx* pm_ctx);

struct upm_hash_ctx {
  pm_hash_ctx pm_ctx;
  ssize_t off;
};
typedef struct upm_hash_ctx upm_hash_ctx;
ssize_t upm_hash(const void* data, ssize_t size, upm_hash_ctx *ctx);

ssize_t md5_hash(const void* data, ssize_t size, void *unused);

