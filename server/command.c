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

char * get_interfaces = "ls /sys/class/net/";
char * get_ip = "ifconfig ens33 | grep 'inet'";
char * get_status = "cat /sys/class/net/eth0/operstate";

command * push_new_command(command * command_list, char *command_text){

    command * new_command = command_list;

    while(new_command->next!=NULL){
        new_command = new_command->next;
    }



    new_command->next = calloc(1,sizeof(command));
    strcpy(new_command->next->command_text,command_text);
    new_command->next->command_arguments_counter =0;
    new_command->next->command_arguments = NULL;
    new_command->next->next = NULL;
    new_command->last=new_command;

    return new_command->next;



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
void validate_command(command *  cmd){

    for(int i=0;i<COMMAND_COUNTER;i++){
        puts(aviable_commands[i]);
    }

}
void set_system_command(char * command_type){}


void prepare_commands(command* cmd){
    command * current_command = cmd->next;
    char * script_text = malloc(sizeof(char) * 200);
    while(current_command->next !=NULL){

        if(strstr(current_command->command_text,"status")){
            script_text = "/home/pdata/Podyplomowka/podstawy_c/zadanie/server/get_if_data.sh status";


            if(current_command->command_arguments_counter >0){
               concat(script_text,current_command->command_arguments->command_argument_value);
                puts("Bellow string will be executed");
                puts(script_text);

            }

        }

        if(strstr(current_command->command_text,"list")){
            puts("Executing \n");
            puts(current_command->command_text);
            execute_bash_script("/home/pdata/Podyplomowka/podstawy_c/zadanie/server/get_if_data.sh list");
        }



        current_command = current_command->next;
    }




}


const char  *  execute_bash_script(char *system_command){
    FILE *pp;
    pp = popen(system_command, "r");
    char *buff_ptr, buff[1024] = "";
    buff_ptr = buff;
    if (pp != NULL) {

        while (1) {
            char *line;
            char buf[1000];
            line = fgets(buf, sizeof buf, pp);
            if (line == NULL) break;
            strcat(buff_ptr,line);
        }
        pclose(pp);
    }

    return buff_ptr;

}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}