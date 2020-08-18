#ifndef _SIN_LINKED_LIST_
#define _SIN_LINKED_LIST_

typedef struct Node Node_t; // linked list node
typedef struct Node_head Node_head_t; // linked list head

struct Node{
    void (*fn_pointer)(); // function callback
    Node_t* next;
    void *data; // dummy data that will/should be used by function callback
};

struct Node_head{
    Node_t* head;
};

Node_head_t* create_linked_list();
Node_t* create_node(void *data);
void _def_function(void *data);
void insert_element(Node_head_t* linked_list_head, Node_t* node);
void iterate_linked_list(Node_head_t* linked_list_head);
void find_node(Node_head_t* linked_list_head, void *data);
void remove_node(Node_head_t* linked_list_head, void *data);
void remove_linked_list_and_free_memory(Node_head_t* linked_list_head);

#endif // _SIN_LINKED_LIST_
