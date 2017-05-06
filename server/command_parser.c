//
// Created by pdata on 29.04.17.
//

#include <memory.h>
#include <stdio.h>
#include <malloc.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#include "command.h"




char * output;


const char *  show_interfaces();
const char  *  execute_bash_script(char *system_command);


void parse_client_input(char *input){
    output = malloc(1024);
    input_to_xml(input, 1024);

    // todo : adding system commands to structure





}
void input_to_xml(const char * client_input, int size) {
    // TODO: Chosing client_input to execute after parsing XML client_input send by client

    xmlDocPtr doc;
    doc = xmlReadMemory(client_input, size, "in-memory-xml", NULL, 0);

    if (doc == NULL) {
        // XML cannot be properly parsed

        output = "Error while parsing client input, make sure your client_input is in proper xml format with root node";
    } else {
        // XML has been parsed;

        command * commands_list = NULL;

        commands_list = calloc(1,sizeof(command));
        commands_list->next = NULL;

        int result = get_commands_list(commands_list,doc);

        if(result > 0){
            printf("%d commands send by client",result);
            prepare_commands(commands_list);
        }
    }

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




