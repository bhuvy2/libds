#include "vector.h"
#include "common.h"
#include <assert.h>
#include <string.h>

static const int INITIAL_CAPACITY = 10;

struct vector {
  void **array;
  size_t size;
  size_t capacity;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_t mtx;
#endif
};

vector *vector_create() {
  vector *ret = malloc(sizeof(vector));
  if(!ret) {
    return NULL;
  }
  ret->size = 0;
  ret->capacity = INITIAL_CAPACITY;
  ret->array = malloc(INITIAL_CAPACITY*sizeof(*ret->array));

#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_init(&ret->mtx, NULL);
#endif

  return ret;
}

void vector_destroy(vector *this) {
  free(this->array);
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_destroy(&this->mtx);
#endif
}

#ifndef LIBDS_PTHREAD_ENABLED
ssize_t vector_size(vector *this) {
  return this->size;
}
#endif

static void vector_expand_capacity(vector *this, ssize_t new_capacity){
  lock_if_enabled(&this->mtx);
  this->array = realloc(this->array, new_capacity);
  this->capacity = new_capacity;
  unlock_if_enabled(&this->mtx);
}


void vector_resize(vector *this, ssize_t new_size) {
  lock_if_enabled(&this->mtx);
  ssize_t new_capacity = this->capacity;
  if (new_size > this->capacity) {
    // TODO: Optimize loops and overflow
    while (new_size > new_capacity) {
      new_capacity *= 2;
    }
  } else {
    while (new_size < new_capacity*2) {
      new_capacity /= 2;
    }
  }
  vector_expand_capacity(this, new_capacity);
  this->size = new_size;
  unlock_if_enabled(&this->mtx);
}

int vector_set(vector *this, ssize_t index, void *str) {
  lock_if_enabled(&this->mtx);
  if (index < 0 || index >= this->size) {
    unlock_if_enabled(&this->mtx);
    return -1;
  }
  this->array[index] = str;
  unlock_if_enabled(&this->mtx);
}

int vector_get(vector *this, ssize_t index, void **ret) {
  lock_if_enabled(&this->mtx);
  if (index < 0 || index >= this->size) {
    unlock_if_enabled(&this->mtx);
    return -1;
  }
  void *elem = this->array[index];
  unlock_if_enabled(&this->mtx);
  *ret = elem;
}

int vector_insert(vector *this, ssize_t index, void *str) {
  lock_if_enabled(&this->mtx);
  if (index < 0) {
    unlock_if_enabled(&this->mtx);
    return -1;
  }
  if(index <= this->size) {
    vector_append(this, NULL);
    memmove(this->array + index + 1, this->array + index, (this->size - index)*sizeof(void*));
    this->array[index] = str;
  }
  else{
    // TODO: Find the greatest power of two
    vector_resize(this, index+1);
    vector_set(this, index, str);
  }
  unlock_if_enabled(&this->mtx);
  return 0;
}

int vector_delete(vector *this, ssize_t index, void **ret) {
  lock_if_enabled(&this->mtx);
  if (this->size == 0 || index < 0 || index >= this->size) {
    return -1;
  }
  void *elem = this->array[index];
  ssize_t to_copy = this->size-1-index;
  memmove(this->array+index, this->array+index+1, to_copy*sizeof(this->array[0]));

  this->size--;
  if(this->size*4 <= this->capacity && this->capacity > INITIAL_CAPACITY) {
    vector_expand_capacity(this, this->capacity/2);
  }
  unlock_if_enabled(&this->mtx);
  if (ret) {
    *ret = elem;
  }
  return 0;
}

int vector_append(vector *this, void *str) {
  lock_if_enabled(&this->mtx);
  if(this->capacity == this->size){
    vector_expand_capacity(this, this->capacity*2);
  }
  this->size++;
  vector_set(this, this->size-1, str);
  unlock_if_enabled(&this->mtx);
  return 0;
}

int vector_pop(vector *this, void **ret) {
  return vector_delete(this, this->size-1, ret);
}
