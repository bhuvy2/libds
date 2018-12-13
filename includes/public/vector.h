#pragma once

#include <stdlib.h>
#include <stdint.h>

struct vector;

typedef struct vector vector;

vector *vector_create();

vector *vector_create_with_size(ssize_t);

vector *vector_shallow_copy(vector *);

vector *vector_concatenate(vector *, vector*);

int vector_equals(vector *, vector *);

vector *vector_slice(vector *, ssize_t lhs, ssize_t rhs);

void vector_clear(vector *this);

void vector_destroy(vector *this);

vector *vector_combinations(vector *vec);

vector *vector_compact(vector *vec);

vector *vector_drop(vector *vec, ssize_t n);

int vector_fill(vector *vec, void *elem, ssize_t lhs, ssize_t rhs);

int vector_filter(vector *vec, int (*decider)(void *));

int vector_map(vector *vec, void *(*decider)(void *));

int vector_reverse(vector *vec, void **ret);

int vector_shuffle(vector *vec);

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


