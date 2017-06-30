//
// Created by pdata on 30.06.17.
//

#ifndef ONE_WRITER_MANY_READERS_LIST_H
#define ONE_WRITER_MANY_READERS_LIST_H
typedef struct List{
    int value;
    struct List* next;
    struct List* previous;
}List;
int get_max_size();
int get_number_of_elements();
int push(int value);
int pop();
#endif //ONE_WRITER_MANY_READERS_LIST_H
