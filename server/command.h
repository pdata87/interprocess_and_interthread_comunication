//
// Created by pdata on 02.05.17.
//

#ifndef ZADANIE_COMMAND_H
#define ZADANIE_COMMAND_H

#endif //ZADANIE_COMMAND_H
typedef struct command{
    char command_text[20]; // list / status  / addr_ip / addr_hw
    struct command_argument* command_arguments; //wskaźnik na listę skladowych polecenia np : if dla xml o strukturze <status><if>eth0</if></status>, dla tego przypadku structura będzie przechowywała listę interfejsów podanych przez clienta
} command;
typedef struct command_argument{
    char  command_argument_value[20];
    struct command_argument * next;
    struct command_argument * last;
    struct command_argument * first;
} command_argument;

command* init_command(char * command_text);
void push_command_argument(command * command,char * element);
void print_command_arguments(command_argument * com_a);
void  validate_command(command *  cmd);
