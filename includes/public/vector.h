#pragma once

#include <stdlib.h>
#include <stdint.h>

struct vector;

typedef struct vector vector;

vector *vector_create();

void vector_destroy(vector *this);

#ifndef LIBDS_PTHREAD_ENABLED
ssize_t vector_size(vector *this);
#endif

// TODO: Change api to return int to check whether the expand failed
void vector_resize(vector *this, ssize_t new_size);

int vector_set(vector *this, ssize_t index, void *str);

int vector_get(vector *vector, ssize_t index, void **ret);

int vector_insert(vector *this, ssize_t index, void *str);

int vector_delete(vector *this, ssize_t index, void **ret);

int vector_append(vector *this, void *str);

int vector_pop(vector *this, void **ret);
