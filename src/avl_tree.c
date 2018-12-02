#include "avl_tree.h"

struct avl_tree_node {
  struct avl_tree_node *left;
  struct avl_tree_node *right;
  void *key;
  void *val;
  int balance_factor;
};

typedef struct avl_tree_node avl_tree_node;

struct avl_tree {
  avl_tree_node *root;
  ssize_t num_elems;
  avl_cmp_func func;
};

avl_tree *new_tree(avl_cmp_func func){
  avl_tree *ret = malloc(sizeof(*ret));
  ret->root = NULL;
  ret->num_elems = 0;
  ret->func = func;
  return ret;
}

void avl_tree_destroy(avl_tree *tree) {
  
}

static avl_tree_node *new_node(void *key, void *val) {
  avl_tree_node *node = malloc(sizeof(*node));
  node->right = NULL;
  node->left = NULL;
  node->balance_factor = 0;
  node->key = key;
  node->val = val;
}

void avl_tree_insert(avl_tree *tree, void *key, void *val){
  if (!tree->root) {
    tree->root = new_node(key, val);
    tree->num_elems++;
    return;
  }
}

void *avl_tree_get(avl_tree *tree, void *key){

}

void avl_tree_delete(avl_tree *tree, void *key){

}

void avl_tree_split(avl_tree* tree, void *key, avl_tree **ret){

}

avl_tree *avl_tree_join(avl_tree *tree, avl_tree *tree2){

}
