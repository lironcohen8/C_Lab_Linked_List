#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/* This struct is in use only by the internal functions of the linked list
and shouldn't be used by the client of this module */
typedef struct _list_node {
    int data;
    struct _list_node* next;
    struct _list_node* prev;
} list_node_t;

/* private functions */
list_node_t* init_node(int val) {
    list_node_t* new_node = (list_node_t*)malloc(sizeof(list_node_t));
    new_node->data = val;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void insert_after_node(linked_list* lst, list_node_t* node, int val) {
    list_node_t* node_to_insert = init_node(val);
    list_node_t* next_node = node->next;
    if (next_node != NULL) {
        next_node->prev = node_to_insert;
        node_to_insert->next = next_node;
    } else {
        lst->tail = node_to_insert;
    }
    node->next = node_to_insert;
    node_to_insert->prev = node;
    lst->len++;
}

void remove_node(linked_list* list, list_node_t* node) {
    if (node == list->head) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node == list->tail) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }
    free(node);
    list->len--;
}

/* public functions */
void init_list(linked_list* lst){
    lst->head = NULL;
    lst->tail = NULL;
    lst->len = 0;
}

void add_end(linked_list* list, int val) {
    list_node_t* new_node = init_node(val);

    if (list->tail == NULL) {
        // Empty list
        list->head = new_node;
    } else {
        // Adding new node to the end of the list
        list->tail->next = new_node;
        new_node->prev = list->tail;
    }

    list->tail = new_node;
    list->len++;
}

void add_start(linked_list* list, int val) {
    list_node_t* new_node = init_node(val);

    if (list->head == NULL) {
        // Empty list
        list->tail = new_node;
    } else {
        // Adding new node at the start of the list
        list->head->prev = new_node;
        new_node->next = list->head;
    }

    list->head = new_node;
    list->len++;
}

bool add_after_val(linked_list* list, int val_to_insert, int val_to_look_for) {
    list_node_t* current_node = list->head;
    while (current_node != NULL) {
        if (current_node->data == val_to_look_for) {
            insert_after_node(list, current_node, val_to_insert);
            return true;
        }
        current_node = current_node->next;
    }
    return false;
}

int first_index_of_val(linked_list* list, int val) {
    list_node_t* current_node = list->head;
    unsigned int index = 0;
    while (current_node != NULL) {
        if (current_node->data == val) {
            return index;
        }
        index++;
        current_node = current_node->next;
    }
    return -1;
}

bool delete_node_at_index(linked_list* list, unsigned int index) {
    list_node_t* temp = list->head;
    if (index > (list->len - 1)) {
        return false;
    }
    for (unsigned int i = 0; i < index; i++) {
        temp=temp->next;
    }
    remove_node(list, temp);
    return true;
}

void print_list(linked_list* list) {
    list_node_t* current_node = list->head;
    if (current_node == NULL) {
        printf("[]\n");
    } else {
        printf("[%d", current_node->data);
        while (current_node->next != NULL) {
            current_node = current_node->next;
            printf(", %d", current_node->data);
        }
        printf("]\n");
    }
}

void free_list(linked_list* list) {
    list_node_t* current_head = list->head;
    list_node_t* node_to_free = NULL;
    while (current_head != NULL) {
        node_to_free = current_head;
        current_head = current_head->next;
        free(node_to_free);
    }
    list->len = 0;
}