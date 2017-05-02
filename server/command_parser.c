//
// Created by pdata on 29.04.17.
//

#include <memory.h>
#include <stdio.h>
#include <malloc.h>
#include "command.h";


FILE *pp;
const char *  show_interfaces();
const char * myFunction();
void parse_client_input(char * c){
    // TODO : Add commands parsing

    int fo = strchr(c,'<');
    int lo = strchr(c,'>');


    command * com = init_command("");
    validate_command(com);



   // print_command_arguments(com->command_arguments);

}

void get_value_between_brakcet(char * command_text){
    int current_char_pos = 0;
    char command[100];

    if(command_text[0]=='<'){
        while(command_text[current_char_pos]!=">"){
            puts("reading command");
            strcat(command,command_text[current_char_pos]);
            current_char_pos++;
        }
    }
    puts(command);

}

//void  show_interfaces(char * output){
//    pp = popen("ip a", "r");
//
//    if (pp != NULL) {
//        while (1) {
//            char *line;
//            char buf[1000];
//            line = fgets(buf, sizeof buf, pp);
//            if (line == NULL) break;
//            strcat(output,line);
//        }
//        pclose(pp);
//    }
//
//
//
//
//}

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

