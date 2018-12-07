#include "queue.h"
#include "ring_buffer.h"
#include "stack.h"
#include "common.h"

#ifdef LIBDS_PTHREAD_ENABLED
#include <pthread.h>
#endif

//TODO: Refactor to have less mutexes
struct queue {
  stack *reader_buffer;
  stack *writer_buffer;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_t mtx;
#endif
};

const static int rb_capacity = 64;

queue *queue_create() {
  queue *ret = malloc(sizeof(*ret));
  ret->reader_buffer = new_stack();
  ret->writer_buffer = new_stack();
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_init(&ret->mtx, NULL);
#endif
}

void queue_destroy(queue *ret) {
  stack_destroy(ret->reader_buffer);
  free(ret->reader_buffer);
  stack_destroy(ret->writer_buffer);
  free(ret->writer_buffer);
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_destroy(&ret->mtx);
#endif
}

#ifndef LIBDS_PTHREAD_ENABLED
ssize_t queue_size(queue *q) {
  return stack_size(q->writer_buffer) + stack_size(q->reader_buffer);
}
#endif

static void queue_switch(queue *q) {
  lock_if_enabled(&q->mtx);
  while (1) {
    void *ret;
    int val = stack_pop(q->writer_buffer, &ret);
    if (val != 0) {
      break;
    }
    stack_push(q->reader_buffer, ret);
  }
  unlock_if_enabled(&q->mtx);
}

int queue_pop(queue *q, void **ret) {
  void *elem;
  int e = stack_pop(q->reader_buffer, &elem);
  if (e != 0) {
    queue_switch(q);
    e = stack_pop(q->reader_buffer, &elem);
  }

  if (e == 0 && ret) {
    *ret = elem;
  }

  return e;
}

int queue_push(queue *q, void *elem) {
  return stack_push(q->writer_buffer, elem);
}
