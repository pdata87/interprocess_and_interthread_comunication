//
// Created by pdata on 30.06.17.
//

#include <stdlib.h>
#include "List.h"
struct List * head = NULL;
struct List * tail = NULL;
int elements_counter =0;
int list_size = 20;
int pop() {
    int ret = -1;

    if(head != NULL) {
        if(head == tail) {
            ret = head->value;
            free(head);
            head = NULL;
            tail = NULL;
        }
        else {
            List* old_head = head;
            ret = head->value;

            head = head->next;
            free(old_head);
        }

    }
    elements_counter --;
    return ret;
}

int push(int value) {
    List* node = malloc(sizeof(List));
    node->value = value;
    node->next = NULL;

    if(head == NULL) {
        head = node;
        tail = node;
    }
    else {
        if(head == tail) {
            tail = node;
            head->next = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    elements_counter++;

}
int get_number_of_elements(){
    return elements_counter;
}
int get_max_size(){
    return  list_size;
}