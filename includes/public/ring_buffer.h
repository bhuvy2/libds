#pragma once
#include <stdlib.h>

struct ring_buffer;

typedef struct ring_buffer ring_buffer;

ring_buffer *ring_buffer_create(ssize_t num_elems);

#ifndef LIBDS_PTHREAD_ENABLED
ssize_t ring_buffer_size(ring_buffer *q);
#endif

void ring_buffer_destroy(ring_buffer *rb);

int ring_buffer_add(ring_buffer *rb, void *elem);

int ring_buffer_pop(ring_buffer *rb, void **ret);
