#include "linked_list.h"

int main(int argc, char const *argv[])
{
    linked_list lst;
    init_list(&lst);

    print_lst(&lst);

    add_start(&lst, 2);
    print_lst(&lst);
    add_start(&lst, 4);
    add_end(&lst, 7);
    print_lst(&lst);

    bool res = add_after_val(&lst, 54, 4);
    res = add_after_val(&lst, 21, 11);
    int index = first_index_from_val(&lst, 54);
    index = first_index_from_val(&lst, 19);
    res = delete_from_index(&lst, 3);
    res = delete_from_index(&lst, 0);

    free_list(&lst);
    return 0;
}
