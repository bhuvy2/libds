#include "avl_tree.h"
#include "stack.h"

struct avl_tree_node {
  struct avl_tree_node *left;
  struct avl_tree_node *right;
  void *key;
  void *val;
  int height;
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
  node->height = 1;
  node->key = key;
  node->val = val;
}

static ssize_t max(ssize_t v1, ssize_t v2) {
  if (v1 <= v2) {
    return v2;
  }
  return v1;
}

static ssize_t node_height(avl_tree_node *node) {
  if (node == NULL) {
    return 0;
  }
  return node->height;
}

static void fix_node_height(avl_tree_node *node) {
  ssize_t left = node_height(node->left);
  ssize_t right = node_height(node->right);
  node->height = max(left, right) + 1;
}

static ssize_t balance_factor(avl_tree_node *node) {
  ssize_t left = node_height(node->left);
  ssize_t right = node_height(node->right);
  return right - left;
}
void avl_tree_insert(avl_tree *tree, void *key, void *val){
  if (!tree->root) {
    tree->root = new_node(key, val);
    tree->num_elems++;
    return;
  }
  avl_tree_node *cur = tree->root;
  avl_tree_node *to_insert = tree->root;
  stack *traversal = new_stack();
  while (1) {
    int cmp_val = tree->func(cur->key, key);
    avl_tree_node *next = NULL;
    if (cmp_val <= 0) {
      if (cur->left == NULL) {
        cur->left = to_insert;
      } else {
        next = cur->left;
      }
    } else {
      if (cur->right == NULL) {
        cur->right = to_insert;
      } else {
        next = cur->right;
      }
    }

    stack_push(traversal, cur);
    if (next) {
      cur = next;
    } else {
      break;
    }
  }

  void *new_node;
  while (stack_pop(traversal, &new_node) == 0) {
    avl_tree_node *node = new_node;
    ssize_t bf = balance_factor(node);
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
