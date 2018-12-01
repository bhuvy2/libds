#include "vector.h"
#include <assert.h>
#include <string.h>

static const int INITIAL_CAPACITY = 10;

struct vector {
  void **array;
  size_t size;
  size_t capacity;
};

vector *vector_create() {
  vector *ret = malloc(sizeof(vector));
  if(!ret) {
    return NULL;
  }
  ret->size = 0;
  ret->capacity = INITIAL_CAPACITY;
  ret->array = malloc(INITIAL_CAPACITY*sizeof(*ret->array));
  return ret;
}

void vector_destroy(vector *this) {
  free(this->array);
}

ssize_t vector_size(vector *this) {
  return this->size;
}

static void vector_expand_capacity(vector *this, ssize_t new_capacity){
  this->array = realloc(this->array, new_capacity);
  this->capacity = new_capacity;
}


void vector_resize(vector *this, ssize_t new_size) {
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
}

void vector_set(vector *this, ssize_t index, void *str) {
  this->array[index] = str;
}

void *vector_get(vector *this, ssize_t index) {
  return this->array[index];
}

void vector_insert(vector *this, ssize_t index, void *str) {
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
}

void *vector_delete(vector *this, ssize_t index) {
  void *elem = this->array[index];
  ssize_t to_copy = this->size-1-index;
  memmove(this->array+index, this->array+index+1, to_copy*sizeof(this->array[0]));

  this->size--;
  if(this->size*4 <= this->capacity && this->capacity > INITIAL_CAPACITY) {
    vector_expand_capacity(this, this->capacity/2);
  }
  return elem;
}

void vector_append(vector *this, void *str) {
  if(this->capacity == this->size){
    vector_expand_capacity(this, this->capacity*2);
  }
  this->size++;
  vector_set(this, this->size-1, str);
}
