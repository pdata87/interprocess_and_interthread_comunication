//
// Created by pdata on 09.05.17.
//

#include <stdio.h>
#include <memory.h>
#include "command.h"
#include "request_handler.h"
#include "string_helpers.h"

void process_request(request *req){

    command * current_command = req->commands_list->next;
    char * script_text = calloc(1024,sizeof(char));
    const char * script_path = "/home/pdata/Podyplomowka/podstawy_c/zadanie/server/get_if_data.sh";


    char * output = calloc(1024,sizeof(char));

        while(current_command !=NULL){


                script_text = concat_with_space(script_path,current_command->command_text);
                command_argument * tmp_a = current_command->command_arguments;
                for(int i=0;i<current_command->command_arguments_counter;i++){
                    perror("process_request_begin");
                    script_text = concat_with_space(script_text,tmp_a->command_argument_value);
                    perror("process_request_end");
                    tmp_a=tmp_a->next; // go to next attribute (example : <if>wlan0</if>
                }
                output = concat_with_new_line(output,execute_bash_script(script_text));



            current_command = current_command->next;
            strcpy(req->response_text,output);
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

//void validate_command(command *  cmd){
//
//    for(int i=0;i<COMMAND_COUNTER;i++){
//        puts(aviable_commands[i]);
//    }
//
//}