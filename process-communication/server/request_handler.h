//
// Created by pdata on 09.05.17.
//

#ifndef ZADANIE_REQUEST_HANDLER_H
#define ZADANIE_REQUEST_HANDLER_H

#endif //ZADANIE_REQUEST_HANDLER_H


typedef struct request{
    int bytes_recv_from_client;
    int no_of_parsed_commands;
    int response_status;
    char response_text[1024];
    command * commands_list;
} request;


void process_request(request *req);
const char  *  execute_bash_script(char *system_command);
