//
// Created by pdata on 02.05.17.
//

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <libxml2/libxml/tree.h>
#include "command.h"
#define  COMMAND_COUNTER 4



char * aviable_commands[] = { "list", "status", "addr_ip","addr_hw"};


command * push_new_command_to_list(command * command_list, char *command_text){


    command * new_command  = command_list;

    while(new_command->next!=NULL){
        new_command = new_command->next;
    }

    new_command->next = calloc(1,sizeof(command));
    strcpy(new_command->next->command_text,command_text);
    new_command->next->command_arguments_counter =0;
    new_command->next->command_arguments = NULL;
    new_command->next->next = NULL;
    new_command->last=new_command;

    return new_command;



}

void push_command_argument(command * cmd,xmlNode * element){
    command_argument * new_argument = calloc(1,sizeof(command_argument));
    new_argument->next = NULL;
    cmd->command_arguments_counter++;
    strcpy(new_argument->command_argument_value,element->content);
    strcpy(new_argument->command_argument_name,element->parent->name);

    if(cmd->command_arguments == NULL){
        // pierwszy element listy
        cmd->command_arguments = new_argument;
        cmd->command_arguments->first= new_argument;
        cmd->command_arguments->last = new_argument;
    }
    else{
        // sprawdzenie czy element poczatkowy jest tożsamy z końcowym, w przeciwnym wypadku ostatni element staja się aktualnym argumentem
        if(cmd->command_arguments->first == cmd->command_arguments->last){
            cmd->command_arguments->next = new_argument;
            cmd->command_arguments->last = new_argument;
        }else {
            cmd->command_arguments->last->next=new_argument;
            cmd->command_arguments->last = new_argument;
        }

    }

}
void print_command_arguments(command_argument * com_a){

    command_argument * current_argument = com_a;


    while(current_argument != NULL){

        puts(current_argument);
        current_argument = current_argument->next;

    }
}



