#pragma once

#include <stdlib.h>
#include <stdint.h>

struct vector;

typedef struct vector vector;

vector *vector_create();

void vector_destroy(vector *this);

ssize_t vector_size(vector *this);

void vector_resize(vector *this, ssize_t new_size);

void vector_set(vector *this, ssize_t index, void *str);

void *vector_get(vector *vector, ssize_t index);

void vector_insert(vector *this, ssize_t index, void *str);

void *vector_delete(vector *this, ssize_t index);

void vector_append(vector *this, void *str);
