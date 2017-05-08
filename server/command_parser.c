//
// Created by pdata on 29.04.17.
//

#include <memory.h>
#include <stdio.h>
#include <malloc.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#include "command.h"

#define XML_PARSING_ERROR             -1






const char *  show_interfaces();
const char  *  execute_bash_script(char *system_command);

char * output;

char * get_parser_output(){

    return output;
}
int parse_client_input(char *input, int size){

    int parsing_status = -1;
    output = malloc(size);
    xmlDocPtr doc;

    doc = xmlReadMemory(input, size, "in-memory-xml", NULL, 0);

    if (doc == NULL) {
        // XML cannot be properly parsed
        return XML_PARSING_ERROR; // -1

    } else {
        // XML has been parsed;

        command * commands_list = NULL;

        commands_list = calloc(1,sizeof(command));
        commands_list->next = NULL;

        int result = get_commands_list(commands_list,doc);

        if(result > 0){

            execute_commands_on_server(commands_list);

        }
        // if 0, input has been properly parsed but return 0 commands, else return number of proper commands
        return result;

    }


    // todo : adding system commands to structure





}


int get_commands_list(command * commands_list,xmlDoc *xml_document){
    int commands_counter = 0;

    xmlNode * root = xml_document->children;
    xmlNode * current_command = root->children;
    xmlNode * current_command_element;

    while(current_command !=NULL){
        commands_counter++;
        // initialize new command structure
        command * tmp_command=NULL;
        tmp_command = push_new_command(commands_list, current_command->name);
        current_command_element = current_command->children;

        while(current_command_element != NULL){
            switch (current_command_element->type){
                case XML_ELEMENT_NODE:

                    printf(current_command_element->name);
                    current_command_element = current_command_element->children;
                    break;
                case XML_TEXT_NODE:

                    printf("\t %s \n",current_command_element->content);
                    push_command_argument(tmp_command,current_command_element);
                    current_command_element = current_command_element->parent->next;

                    break;
                default:

                    break;
            }


        }

        current_command = current_command->next;
    }
    return commands_counter;
}




