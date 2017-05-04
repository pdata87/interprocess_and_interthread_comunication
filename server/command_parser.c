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



const char *  show_interfaces();
const char * myFunction();
 void process_client_input(char * input){
    // TODO : Add commands parsing
    parse_xml_command(input,1024);


   // command * com = init_command("");
   // validate_command(com);



   // print_command_arguments(com->command_arguments);

}
void parse_xml_command(const char * command,int size){
    xmlDocPtr doc;
    doc = xmlReadMemory(command,size,"noname.xml",NULL,0);

    if(doc == NULL){
        puts("Error while parsing client input");
    }else{

        xmlNode * root = doc->children;
        xmlNode * current_command = root->children;
        xmlNode * current_command_element;
        while(current_command !=NULL){
                puts(current_command->name);
                current_command_element = current_command->children;
                while(current_command_element != NULL){
                        switch (current_command_element->type){
                            case XML_ELEMENT_NODE:
                                puts(current_command_element->name);
                                current_command_element= current_command_element->children;
                                break;
                            case XML_TEXT_NODE:
                                puts("/t");
                                puts(current_command_element->content);
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




const char  *  show_interfaces(){
    pp = popen("ifconfig", "r");
    char *BUFF = malloc(sizeof(char)*5000);
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
    //puts(BUFF);
    return BUFF;




}

