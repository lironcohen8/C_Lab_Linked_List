#include "linked_list.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LINE_LEN 100
#define MAX_WORDS_IN_COMMAND 3

/* private functions */
void convert_user_input_to_lowercase(char user_input[]) {
    for (unsigned int i = 0; i < strlen(user_input); i++) {
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
    int command_arg_1 = atoi(command[1]);
    int command_arg_2 = atoi(command[2]);
    if (strcmp(command_name, "add_end") == 0) {
        add_end(lst, command_arg_1);
    } else if (strcmp(command_name, "add_start") == 0) {
        add_start(lst, command_arg_1);
    } else if (strcmp(command_name, "add_after") == 0) {
        if (add_after_val(lst, command_arg_1, command_arg_2) == false) {
            printf("value %d is not found, exiting the program.", command_arg_2);
            free_list(lst);
            exit(1);
        }
    } else if (strcmp(command_name, "index") == 0) {
        printf("%d\n", first_index_of_val(lst, command_arg_1));
    } else if (strcmp(command_name, "del") == 0) {
        if (delete_node_at_index(lst, command_arg_1) == false) {
            printf("index %d is too large for list of length %d, exiting the program.", command_arg_1, lst->len);
            free_list(lst);
            exit(1);
        }
    } else if (strcmp(command_name, "print") == 0) {
        print_list(lst);
    } else { // exit 
        free_list(lst);
        exit(0);
    }
}

int main()
{
    linked_list lst;
    init_list(&lst);

    char user_input[MAX_INPUT_LINE_LEN];
    char* command[MAX_WORDS_IN_COMMAND];

    while (true) {
        fgets(user_input, sizeof(user_input), stdin);
        convert_user_input_to_lowercase(user_input);
        parse_user_input_into_command(user_input, command);
        execute_command(&lst, command);
    }

    free_list(&lst);
    return 0;
}
