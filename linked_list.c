#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

#define INT_TO_CHAR(x) ((x) + '0')

/* private functions */
node_t* init_node(int val) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = val;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

unsigned int get_string_len(unsigned int list_len) {
    if (list_len > 0) {
        // 2 for brackets, (list_len) for elements, (list_len - 1) for commas, (list_len - 1) for spaces, 1 for '\0'
        return 2 + list_len + 2 * (list_len - 1) + 1;
    } else {
        // for empty list "[]\0"
        return 3;
    }   
}

void insert_after(linked_list* lst, node_t* node, int val) {
    node_t* inserted_node = init_node(val);
    node_t* next_node = node->next;
    if (next_node != NULL) {
        next_node->prev = inserted_node;
        inserted_node->next = next_node;
    } else {
        lst->tail = inserted_node;
    }
    node->next = inserted_node;
    inserted_node->prev = node;
    lst->len++;
}

void remove_node(linked_list* list, node_t* node) {
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
    node_t* new_node = init_node(val);

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
    node_t* new_node = init_node(val);

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

bool add_after_val(linked_list* list, int val_to_insert, int val_to_look) {
    node_t* temp = list->head;
    while (temp != NULL) {
        if (temp->data == val_to_look) {
            insert_after(list, temp, val_to_insert);
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int first_index_from_val(linked_list* list, int val) {
    node_t* temp = list->head;
    unsigned int index = 0;
    while (temp != NULL) {
        if (temp->data == val) {
            return index;
        }
        index++;
        temp = temp->next;
    }
    return -1;
}

bool delete_from_index(linked_list* list, unsigned int index) {
    node_t* temp = list->head;
    if (index > (list->len - 1)) {
        return false;
    }
    for (unsigned int i = 0; i < index; i++) {
        temp=temp->next;
    }
    remove_node(list, temp);
    return true;
}

void print_lst(linked_list* list) {
    unsigned int str_len = get_string_len(list->len);
    char* result = (char*) malloc(str_len);

    result[0] = '[';
    result[str_len - 2] = ']';
    result[str_len - 1] = '\0';

    unsigned int offset = 1;
    node_t* tmp = list->head;
    while (tmp != NULL) {
        result[offset] = INT_TO_CHAR(tmp->data);
        if (tmp->next != NULL) {
            result[offset + 1] = ',';
            result[offset + 2] = ' ';
            offset += 3;
        }
        tmp = tmp->next;
    }

    printf("%s\n", result);
}

void free_list(linked_list* list) {
    node_t* current_head = list->head;
    node_t* node_to_free = NULL;
    while (current_head != NULL) {
        node_to_free = current_head;
        current_head = current_head->next;
        free(node_to_free);
    }
    list->len = 0;
}