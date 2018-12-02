#pragma once

struct avl_tree;

#include "stdlib.h"

typedef struct avl_tree avl_tree;

typedef int (*avl_cmp_func)(void*,void*);

avl_tree *new_tree(avl_cmp_func func);

void avl_tree_destroy(avl_tree *tree);

void avl_tree_insert(avl_tree *tree, void *key, void *val);

void *avl_tree_get(avl_tree *tree, void *key);

void avl_tree_delete(avl_tree *tree, void *key);

void avl_tree_split(avl_tree* tree, void *key, avl_tree **ret);

avl_tree *avl_tree_join(avl_tree *tree, avl_tree *tree2);
