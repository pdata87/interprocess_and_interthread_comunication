//
// Created by pdata on 02.05.17.
//

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "command.h"
#define  COMMAND_COUNTER 4
char * aviable_commands[] = { "list", "status", "addr_ip","addr_hw"};
command* init_command(char * command_text){
    command * cmd = malloc(sizeof(command));
    strcpy(cmd->command_text,command_text);
    cmd->command_arguments = NULL;

    return cmd;

}

void push_command_argument(command * cmd,char * element){


        command_argument * new_argument = malloc(sizeof(command_argument));
        new_argument->next = NULL;
        strcpy(new_argument->command_argument_value,element);

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
void  validate_command(command *  cmd){

    for(int i=0;i<COMMAND_COUNTER;i++){
        puts(aviable_commands[i]);
    }

}