#include <stdio.h>
#include <stdlib.h>
#include "SinglyLinkedList.h"

Node_head_t*
create_linked_list(){ //Create head of linked list
    Node_head_t* linked_list_head;
    linked_list_head = (Node_head_t *)malloc(sizeof(Node_head_t));
    linked_list_head->head = NULL;
    return linked_list_head;
}

Node_t*
create_node(void *data){
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->data = data;
    node->fn_pointer = _def_function;
    return node;
}

void
_def_function(void *data){
    // Dummy function callback
    // Change data type cast if other data type (other then int) will be hold in linked list
    // Implementetaion of data handling goes here
    printf("Dummy - data: %d\n",*((int *)data)); // dummy element typecast
}

void
insert_element(Node_head_t* linked_list_head, Node_t* node){
    if(linked_list_head == NULL){
        printf("First function -> create_linked_list() should be called");
        return;
    }

    if(linked_list_head->head == NULL){
        linked_list_head->head = node;
        linked_list_head->head->next = NULL;
    }else{
        Node_t* previous_head = linked_list_head->head;
        linked_list_head->head = node;
        linked_list_head->head->next = previous_head;
    }
}

void
iterate_linked_list(Node_head_t* linked_list_head){
    Node_t* node =  linked_list_head->head;
    while(node != NULL){
        node->fn_pointer(node->data);
        node = node->next;
    }
}

void
find_node(Node_head_t* linked_list_head, void *data){ // Compare and find by data hold in linked list
    Node_t* node =  linked_list_head->head;
    while(node != NULL){
        if(*((int *)(node->data)) == *((int *)data)){ // Change data type cast if other data type (other then int) will be hold in linked list ...
            node->fn_pointer(node->data);
        }
        node = node->next;
    }
}

void
remove_node(Node_head_t* linked_list_head, void *data){ // Remove node that hold data - only first found
    Node_t* node =  linked_list_head->head;
    Node_t* prev_node = node;
    while(node != NULL){
        // Don't forget to change data type cast if other data type (other then int) will be hold in linked list ...
        if(*((int *)(node->data)) == *((int *)data)){
            if(node == prev_node){
                linked_list_head->head = node->next;
                free(node);
                break;
            }
            prev_node->next = node->next;
            free(node);
            break;
        }
        prev_node = node;
        node = node->next;
    }
}

void
remove_linked_list_and_free_memory(Node_head_t* linked_list_head){ // Destroy linked list and free memory
    Node_t* node =  linked_list_head->head;
    Node_t* next_node = node;

    while(node != NULL){
        next_node = node->next;
        free(node);
        node = next_node;
    }
    linked_list_head->head = NULL;
    free(linked_list_head);
}
