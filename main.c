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
    return 0;
}
