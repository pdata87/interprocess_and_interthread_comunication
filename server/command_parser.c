//
// Created by pdata on 29.04.17.
//

#include <memory.h>
#include <stdio.h>
#include <malloc.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#include "command.h"


FILE *pp;
char * output;


const char *  show_interfaces();
const char  *  execute_system_command(char * system_command);


void parse_client_input(char *input){
    output = malloc(1024);
    parse_to_xml(input,1024);

    // todo : adding system commands to structure

    char * command = "ifconfig -a | sed 's/[ \\t].*//;/^$/d' | tr -d ':'";
    puts(execute_system_command(command));

   // command * com = init_command("");
   // validate_command(com);

    puts(output);

   // print_command_arguments(com->command_arguments);

}
void parse_to_xml(const char * command,int size){
    // TODO: Chosing command to execute after parsing XML command send by client

    xmlDocPtr doc;
    doc = xmlReadMemory(command,size,"in-memory-xml",NULL,0);

    if(doc == NULL){
        // XML cannot be properly parsed;
        output = "Error while parsing client input, make sure your command is in proper xml format with root node";
    }
    else{

        xmlNode * root = doc->children;
        xmlNode * current_command = root->children;
        xmlNode * current_command_element;
        while(current_command !=NULL){

                puts(current_command->name);
                current_command_element = current_command->children;
                while(current_command_element != NULL){
                        switch (current_command_element->type){
                            case XML_ELEMENT_NODE:

                                printf(current_command_element->name);
                                current_command_element = current_command_element->children;
                                break;
                            case XML_TEXT_NODE:

                                printf("\t %s \n",current_command_element->content);

                                current_command_element = current_command_element->parent->next;

                                break;
                            default:

                                break;
                        }


                }

            current_command = current_command->next;
        }
    }


}




const char  *  show_interfaces_list(){
    pp = popen("ifconfig -a | sed 's/[ \\t].*//;/^$/d' | tr -d ':'", "r");
    char *BUFF = malloc(sizeof(char)*1024);
    if (pp != NULL) {

        while (1) {
            char *line;
            char buf[1000];
            line = fgets(buf, sizeof buf, pp);
            if (line == NULL) break;
            strcat(BUFF,line);
        }
        pclose(pp);
    }

    return BUFF;




}

 const char  *  execute_system_command(char * system_command){

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
     printf("a points at this memory location: %p", buff_ptr);
    return buff_ptr;

}

