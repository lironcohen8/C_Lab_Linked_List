#include "linked_list.h"

int main(int argc, char const *argv[])
{
    linked_list lst;
    init_list(&lst);

    print_list(&lst);

    add_start(&lst, 2);
    print_list(&lst);
    add_start(&lst, 4);
    add_end(&lst, 7);
    print_list(&lst);
    for (int i = 0; i < 20; i++)
    {
        add_end(&lst, i);
    }
    print_list(&lst);
    bool res = add_after_val(&lst, -54, 4);
    print_list(&lst);
    res = add_after_val(&lst, 21, 11);
    print_list(&lst);
    int index = first_index_of_val(&lst, 54);
    print_list(&lst);
    index = first_index_of_val(&lst, 19);
    res = delete_node_from_index(&lst, 3);
    print_list(&lst);
    res = delete_node_from_index(&lst, 0);
    print_list(&lst);

    free_list(&lst);
    return 0;
}
