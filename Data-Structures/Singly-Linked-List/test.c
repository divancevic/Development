#include <stdio.h>
#include <stdlib.h>
#include "SinglyLinkedList.h"

int main()
{
    Node_head_t* ll = create_linked_list();

    int element1 = 1; // dummy element
    insert_element(ll,create_node((void *)&element1));

    int element2 = 2; // dummy element
    insert_element(ll,create_node((void *)&element2));

    int element3 = 3; // dummy element
    insert_element(ll,create_node((void *)&element3));

    iterate_linked_list(ll);
    remove_node(ll,(void *)&element3);
    remove_node(ll,(void *)&element1);
    iterate_linked_list(ll);
    remove_linked_list_and_free_memory(ll);

    return 0;
}
