#include <stdlib.h>
#include "ring_buffer.h"
#include "common.h"

#ifdef LIBDS_PTHREAD_ENABLED
#include <pthread.h>
#endif

struct ring_buffer{
  void **elems;
  ssize_t capacity;
  void **to_insert;
  void **to_pop;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_t mtx;
#endif
};

ring_buffer *ring_buffer_create(ssize_t num_elems){
  ring_buffer *rb = malloc(sizeof(*rb));
  rb->capacity = num_elems;
  rb->elems = malloc(rb->capacity*sizeof(*rb->elems));
  rb->to_insert = rb->to_pop = rb->elems;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_init(&rb->mtx, NULL);
#endif
}

void ring_buffer_destroy(ring_buffer *rb) {
  free(rb->elems);
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_destroy(&rb->mtx);
#endif
}

static int ring_buffer_empty(ring_buffer *rb) {
  lock_if_enabled(&rb->mtx);
  int ret = rb->to_insert == rb->to_pop;
  unlock_if_enabled(&rb->mtx);
  return ret;
}

static int ring_buffer_full(ring_buffer *rb) {
  int ret = rb->to_insert + 1 == rb->to_pop ||
    rb->to_pop == rb->elems && rb->to_insert == rb->elems + rb->capacity - 1;
  return ret;
}

int ring_buffer_add(ring_buffer *rb, void *elem){
  lock_if_enabled(&rb->mtx);
  if (ring_buffer_full(rb)) {
    unlock_if_enabled(&rb->mtx);
    return -1;
  }
  rb->to_insert = elem;
  rb->to_insert++;
  if (rb->to_insert - rb->elems == rb->capacity) {
    rb->to_insert = rb->elems;
  }
  unlock_if_enabled(&rb->mtx);
  return 0;
}

int ring_buffer_pop(ring_buffer *rb, void **ret){
  lock_if_enabled(&rb->mtx);
  if (ring_buffer_empty(rb)) {
    unlock_if_enabled(&rb->mtx);
    return -1;
  }
  void *elem = *rb->to_pop;
  rb->to_pop++;
  if (rb->to_pop - rb->elems == rb->capacity) {
    rb->to_pop = rb->elems;
  }
  unlock_if_enabled(&rb->mtx);
  if (ret) {
    *ret = elem;
  }
  return 0;
}

#ifndef LIBDS_PTHREAD_ENABLED
ssize_t ring_buffer_size(ring_buffer *q) {
  if (q->to_pop <= q->to_insert) {
    return q->to_insert - q->to_pop;
  }
  return q->capacity - (q->to_pop - q->to_insert - 1);
}
#endif
