#include "linked_list.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LINE_LEN 100
#define MAX_WORDS_IN_COMMAND 3

/* private functions */
void convert_user_input_to_lowercase(char user_input[]) {
    for (size_t i = 0; i < strlen(user_input); i++) {
        user_input[i] = tolower(user_input[i]);
    }
}

void parse_user_input_into_command(char user_input[], char* command[]) {
    int word_count = 0;
    char* token = strtok(user_input, " \n");
    while (token != NULL) {
        command[word_count] = token;
        word_count++;
        token = strtok(NULL, " \n");
    }
    // Initialize remaining elements of command array to "\0"
    for (int i = word_count; i < MAX_WORDS_IN_COMMAND; i++) {
        command[i] = "\0";
    }
}

void execute_command(linked_list* lst, char* command[]) {
    char* command_name = command[0];

    if (strcmp(command_name, "add_end") == 0) {
        int val = atoi(command[1]);
        add_end(lst, val);
    }
    else if (strcmp(command_name, "add_start") == 0) {
        int val = atoi(command[1]);
        add_start(lst, val);
    }
    else if (strcmp(command_name, "add_after") == 0) {
        int val_to_insert = atoi(command[1]);
        int val_to_look_for = atoi(command[2]);
        if (add_after_val(lst, val_to_insert, val_to_look_for) == false) {
            printf("value %d is not found, exiting the program.", val_to_look_for);
            exit(1);
        }
    }
    else if (strcmp(command_name, "index") == 0) {
        int val = atoi(command[1]);
        printf("%d\n", first_index_of_val(lst, val));
    }
    else if (strcmp(command_name, "del") == 0) {
        int index = atoi(command[1]);
        if (delete_node_at_index(lst, index) == false) {
            printf("index %d is too large for list of length %d, exiting the program.", index, lst->len);
            exit(1);
        }
    }
    else if (strcmp(command_name, "print") == 0) {
        print_list(lst);
    }
    else { // exit 
        free_list(lst);
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    linked_list lst;
    init_list(&lst);

    char user_input[MAX_INPUT_LINE_LEN];
    char* command[MAX_WORDS_IN_COMMAND];

    while (1) {
        fgets(user_input, sizeof(user_input), stdin);
        convert_user_input_to_lowercase(user_input);
        parse_user_input_into_command(user_input, command);
        execute_command(&lst, command);
        // TODO: Delete printing before submission
        print_list(&lst);
    }

    free_list(&lst);
    return 0;
}
