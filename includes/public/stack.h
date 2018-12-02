#pragma once
#include <stdlib.h>

struct stack;

typedef struct stack stack;

stack *new_stack();

void stack_destroy(stack *st);

// If you think you need this functionality in your multithreaded
// Program, you shoule drethink your design

#ifndef LIBDS_PTHREAD_ENABLED
int stack_empty(stack *st);

ssize_t stack_size(stack *st);

int stack_peek(stack *st, void **ret);
#endif

int stack_pop(stack *st, void **ret);

int stack_push(stack *st, void *elem);
