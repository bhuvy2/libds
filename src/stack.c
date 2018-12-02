
#include "vector.h"
#include "stack.h"

struct stack{
  vector *elems;
};

stack *new_stack() {
  stack *ret = malloc(sizeof(*ret));
  ret->elems = vector_create();
  return ret;
}

void stack_destroy(stack *st) {
  vector_destroy(st->elems);
  free(st->elems);
}

#ifndef LIBDS_PTHREAD_ENABLED
int stack_empty(stack *st) {
  return vector_size(st->elems) == 0;
}

ssize_t stack_size(stack *st){
  return vector_size(st->elems);
}

int stack_peek(stack *st, void **ret){
  ssize_t size = vector_size(st->elems);
  return vector_get(st->elems, size-1, ret);
}
#endif

int stack_pop(stack *st, void **ret){
  return vector_pop(st->elems, ret);
}

int stack_push(stack *st, void *elem){
  return vector_append(st->elems, elem);
}
