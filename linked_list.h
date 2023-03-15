#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct _node {
    int data;
    struct _node* next;
    struct _node* prev;
} node_t;

typedef struct _linked_list {
    node_t* head;
    node_t* tail;
    unsigned int len;
} linked_list;

void init_list(linked_list* lst);

void add_end(linked_list* list, int val);

void add_start(linked_list* list, int val);

bool add_after_val(linked_list* list, int val_to_insert, int val_to_look);

int first_index_from_val(linked_list* list, int val);

bool delete_from_index(linked_list* list, unsigned int index);

void print_lst(linked_list* list);

void free_list(linked_list* list);

#endif