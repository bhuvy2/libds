#include "linked_list.h"
#include "common.h"
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _linked_list_node {
  struct _linked_list_node *next;
  void *payload;
} linked_list_node;

struct linked_list {
  linked_list_node *head;
  ssize_t length;
  pthread_mutex_t *mutex;
};

typedef struct linked_list linked_list;

linked_list *linked_list_create() {
  linked_list *ptr = malloc(sizeof(*ptr));
  ptr->head = NULL;
  ptr->length = 0;
  if (pthread_linked()) {
    ptr->mutex = malloc(sizeof(*ptr->mutex));
    pthread_mutex_init(ptr->mutex, NULL);
  }
  return ptr;
}

void linked_list_destroy(linked_list *ptr) {
  linked_list_node *cur = ptr->head;
  while (cur) {
    linked_list_node *next = cur->next;
    free(cur);
    cur = next;
  }
  if (pthread_linked()) {
    pthread_mutex_destroy(ptr->mutex);
    free(ptr->mutex);
  }
}

void linked_list_append(linked_list *ll, void *data) {
  linked_list_node *node = malloc(sizeof(*node));
  node->payload = data;

  if (pthread_linked()) {
    pthread_mutex_lock(ll->mutex);
  }

  node->next = ll->head;
  ll->head = node;
  ll->length++;

  if (pthread_linked()) {
    pthread_mutex_unlock(ll->mutex);
  }
}

void *linked_list_dequeue(linked_list *ll) {
  if (!ll->head) {
    return NULL;
  }

  if (pthread_linked()) {
    pthread_mutex_lock(ll->mutex);
  }

  linked_list_node *node = ll->head;
  ll->head = ll->head->next;
  ll->length--;

  if (pthread_linked()) {
    pthread_mutex_unlock(ll->mutex);
  }

  void *ret = node->payload;
  free(node);

  return ret;
}
