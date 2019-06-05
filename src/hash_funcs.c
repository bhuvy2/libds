#include "hash_funcs.h"
#include <string.h>

#if 0
#include <crypto/hash.h>
#include <linux/err.h>
#include <linux/scatterlist.h>

char *invoke_hash(const void* data, ssize_t size, const char *hash_name) {
  struct scatterlist sg;
  struct crypto_ahash *tfm;
  struct ahash_request *req;

  tfm = crypto_alloc_ahash(hash_name, 0, CRYPTO_ALG_ASYNC);
  if (IS_ERR(tfm)) {
    return NULL;
  }
  unsigned int crypto_size = crypto_ahash_digestsize(tfm);
  char *result = malloc(crypto_size);

  sg_init_one(&sg, data, size);

  req = ahash_request_alloc(tfm, GFP_ATOMIC);
  if (!req) {
    return NULL;
  }

  ahash_request_set_callback(req, 0, NULL, NULL);
  ahash_request_set_crypt(req, sg, result, 1);

  if (crypto_ahash_digest(req)) {
    return NULL;
  }

  ahash_request_free(req);
  crypto_free_ahash(tfm);
  return result;
}

ssize_t md5_hash(const void* data, ssize_t size, void *unused) {
  char *res = invoke_hash(data, size, "md5");

if (!res) {
  return -1;
 }
}
#endif

ssize_t upm_hash(const void *data, ssize_t size, upm_hash_ctx *upm_ctx) {
  const ssize_t off = upm_ctx->off;
  const ssize_t mult = upm_ctx->pm_ctx.mult;
  const ssize_t prime = upm_ctx->pm_ctx.prime;
  const ssize_t hash_size = upm_ctx->pm_ctx.hash_size;
  ssize_t ret = 0;
  const ssize_t *data_s = data;
  ssize_t i;
  for (i = 0; i < size; i += sizeof(ssize_t)) {
    ret += ((data_s[i / sizeof(ssize_t)] * mult + off) % prime) % hash_size;
  }
  ssize_t rem = sizeof(ssize_t) - (i % sizeof(ssize_t));
  if (rem != 0) {
    ssize_t last = 0;
    //TODO: Make this platform independent
    memcpy(&rem, ((char *)&ret) + size - rem, rem);
    ret += ((data_s[i / sizeof(ssize_t)] * mult + off) % prime) % hash_size;
  }
  return ret;
}

ssize_t pm_hash(const void *data, ssize_t size, pm_hash_ctx *pm) {
  upm_hash_ctx ctx;
  ctx.pm_ctx = *pm;
  ctx.off = 0;
  return upm_hash(data, size, &ctx);
}

// http://www.partow.net/programming/hashfunctions/#RSHashFunction

ssize_t rs_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
  ssize_t b    = 378551;
  ssize_t a    = 63689;
  ssize_t hash = 0;
  for(ssize_t i = 0; i < size; i++) {
    hash = hash * a + str[i];
    a = a * b;
  }

  return hash;
}

ssize_t js_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
  ssize_t hash = 1315423911;
  for(ssize_t i = 0; i < size; i++) {
    hash ^= ((hash << 5) + str[i] + (hash >> 2));
  }
  return hash;
}

ssize_t elf_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   ssize_t hash = 0;
   ssize_t x    = 0;

   for(ssize_t i = 0; i < size; i++) {
      hash = (hash << 4) + str[i];
      if((x = hash & 0xF0000000L) != 0) {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}

ssize_t bkdr_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   const ssize_t salt = 131; // 31 131 1313 13131 131313 etc..
   ssize_t hash = 0;
   for(ssize_t i = 0; i < size; i++) {
     hash *= salt;
     hash += str[i];
   }
   return hash;
}

ssize_t sdbm_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   ssize_t hash = 0;
   for(ssize_t i = 0; i < size; i++) {
     hash -= str[i] + (hash << 6) + (hash << 16);
   }
   return hash;
}

ssize_t djb_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   ssize_t hash = 5381;
   for(ssize_t i = 0; i < size; i++) {
      hash += (hash << 5) + str[i];
   }
   return hash;
}

ssize_t dek_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   ssize_t hash = size;
   for(ssize_t i = 0; i < size; i++) {
      hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
   }
   return hash;
}


ssize_t bp_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   ssize_t hash = 0;
   for(ssize_t i = 0; i < size; i++){
     hash = (hash << 7) ^ str[i];
   }
   return hash;
}


ssize_t fnv_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   const ssize_t fnv_prime = 0x811C9DC5;
   ssize_t hash = 0;
   for(ssize_t i = 0; i < size; i++) {
      hash *= fnv_prime;
      hash ^= str[i];
   }
   return hash;
}


ssize_t ap_hash(const char *str, ssize_t size, __attribute__((unused)) void *meta) {
   ssize_t hash = 0xAAAAAAAA;
   for(ssize_t i = 0; i < size; i++) {
     ssize_t xor;
     if (i & 1 == 0) {
       xor = (hash << 7) & str[i] * (hash >> 3);
     } else {
       xor = ~((hash << 11) + (str[i] ^ (hash >> 5)));
     }
     hash ^= xor;
   }
   return hash;
}
