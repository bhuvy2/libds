#include "linked_list.h"
#include "common.h"
#include <stdint.h>
#include <stdlib.h>

#ifdef LIBDS_PTHREAD_ENABLED
#include <pthread.h>
#endif

typedef struct _linked_list_node {
  struct _linked_list_node *next;
  void *payload;
} linked_list_node;

struct linked_list {
  linked_list_node *head;
  ssize_t length;
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_t *mutex;
#endif
};

typedef struct linked_list linked_list;

linked_list *linked_list_create() {
  linked_list *ptr = malloc(sizeof(*ptr));
  ptr->head = NULL;
  ptr->length = 0;

#ifdef LIBDS_PTHREAD_ENABLED
  ptr->mutex = malloc(sizeof(*ptr->mutex));
  pthread_mutex_init(ptr->mutex, NULL);
#endif

  return ptr;
}

void linked_list_destroy(linked_list *ptr) {
  linked_list_node *cur = ptr->head;
  while (cur) {
    linked_list_node *next = cur->next;
    free(cur);
    cur = next;
  }
#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_destroy(ptr->mutex);
  free(ptr->mutex);
#endif
}

void linked_list_append(linked_list *ll, void *data) {
  linked_list_node *node = malloc(sizeof(*node));
  node->payload = data;

#ifdef LIBDS_PTHREAD_ENABLED
  pthread_mutex_lock(ll->mutex);
#endif

  node->next = ll->head;
  ll->head = node;
  ll->length++;

#ifdef LIBDS_PTHREAD_ENABLED
    pthread_mutex_unlock(ll->mutex);
#endif
}

void *linked_list_dequeue(linked_list *ll) {
  if (!ll->head) {
    return NULL;
  }

#ifdef LIBDS_PTHREAD_ENABLED
    pthread_mutex_lock(ll->mutex);
#endif

  linked_list_node *node = ll->head;
  ll->head = ll->head->nexttarget_compile_definitions;
  ll->length--;

#ifdef LIBDS_PTHREAD_ENABLED
    pthread_mutex_unlock(ll->mutex);
#endif

  void *ret = node->payload;
  free(node);

  return ret;
}
