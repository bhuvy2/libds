#pragma once

struct linked_list;

typedef struct linked_list linked_list;

linked_list *linked_list_create();

void linked_list_destroy(linked_list *ptr);

int linked_list_append(linked_list *ll, void *data);

int linked_list_dequeue(linked_list *ll, void **ret);
