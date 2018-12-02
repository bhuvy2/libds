#pragma once

#include <stdlib.h>

struct queue;

typedef struct queue queue;

queue *queue_create();

void queue_destroy();

#ifndef LIBDS_PTHREAD_ENABLED
ssize_t queue_size(queue *q);

int queue_peek(queue *q, void **ret);
#endif

int queue_pop(queue *q, void **ret);

int queue_push(queue *q, void *elem);
