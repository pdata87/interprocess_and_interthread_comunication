#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <zconf.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <sys/ioctl.h>

#include "request_handler.h"
#include "configuration.h"
#include <errno.h>






// this function parses data sent by client
request *  handle_client_request(int client_fd) {

    request * client_request= calloc(1,sizeof(request));
    client_request->commands_list = calloc(1,sizeof(command));
    client_request->response_text = calloc(1024,sizeof(char));
    client_request->response_status = -1;
    client_request->bytes_recv_from_client = recv(client_fd, client_request->client_input, sizeof(client_request->client_input), 0);

    switch( client_request->bytes_recv_from_client){

        case -1 :
            perror("Failed to receive DATA from client: ");

            client_request->response_status = -1;
            strcpy(client_request->response_text,"");
            break;

        case 0 :
            printf(" Connection closed by client\n");
            client_request->response_status = 0;
            strcpy(client_request->response_text,"Client closed connection");
            break ;



        default:
            // if client send data, try parse
            // number of properly (in case of any ) parsed commands
            client_request->no_of_parsed_commands = parse_xml(client_request, strlen(client_request->client_input));

            if(client_request->no_of_parsed_commands > 0){
                client_request->response_status = client_request->no_of_parsed_commands;
                process_request(client_request, get_config_option("bash_script_path"));

            }



            break;

    }
    // send response to client
    send(client_fd, client_request->response_text, 1024, 0);

    // clean xml lib structures;
    xmlCleanupParser();
    xmlDictCleanup();
    xmlCleanupGlobals();
    xmlCleanupMemory();
    return client_request;

}



int main() {
    // Change to tcp ip sockets
    int listeningSocket;
    struct sockaddr_in srv_addr;
    struct pollfd poll_fds[50];
    int clients_fds_counter = 1;
    int return_value, on = 1;
    int poll_size, i = 0;
    int new_client_fd = -1;
    int close_conn;
    memset(&srv_addr,0,sizeof(srv_addr));

    close_conn = 0;


    init_configuration("/home/pdata/Podyplomowka/podstawy_c/zadanie/server/config");



    srv_addr.sin_port = htons(atoi(get_config_option("port")));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);





    listeningSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);

    if (listeningSocket == -1) {
        printf("%s\n", "Couldnt create socket");
    }
    return_value = setsockopt(listeningSocket, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));

    if (return_value < 0) {
        perror("setsockopt() failed");
        close(listeningSocket);
    }
    return_value = ioctl(listeningSocket,FIONBIO,(char*)&on);

    if (return_value < 0)
    {
        perror("ioctl() failed");
        close(listeningSocket);
        exit(-1);
    }
    return_value = bind(listeningSocket, (struct sockaddr *) &srv_addr, sizeof(struct sockaddr_in));

        if (return_value == -1) {
            perror("Error: ");
            printf("%s\n", "Couldnt bind to");
            close(listeningSocket);
        }

        //przypisanie pamieci pod  tablice z poll

        return_value = listen(listeningSocket,  atoi(get_config_option("max_clients")));
        if (return_value < 0) {
            puts("Failed to listen");
            close(listeningSocket);
            exit(-1);
        }
            memset(poll_fds, 0, sizeof(poll_fds));
            puts("Waiting for clients");
            poll_fds[0].fd = listeningSocket;
            poll_fds[0].events = POLLIN;
            int timeout = (3 * 60 * 1000);

            do {

                printf("Waiting on poll()...\n");

                return_value = poll(poll_fds, clients_fds_counter, timeout);

                if (return_value < 0) {
                    perror("  poll failed");
                    break;
                }


                if (return_value == 0) {
                    printf("  poll() timed out.  End program.\n");
                    break;
                }

                poll_size = clients_fds_counter;

                for (i = 0; i < poll_size; i++) {
                    if (poll_fds[i].revents == 0)
                        continue;


                    if (poll_fds[i].revents != POLLIN) {
                        printf("  Error! revents = %d\n", poll_fds[i].revents);
                        //TODO: end_server
                        //end_server = TRUE;
                        break;

                    }
                    // Listening file descriptor
                    if (poll_fds[i].fd == listeningSocket) {
                        // i == 0 - listening socket
                        printf("  Listening socket is readable\n");

                        do {

                            new_client_fd = accept(listeningSocket, NULL, NULL);
                            if (new_client_fd < 0) {
                                if (errno != EWOULDBLOCK) {
                                    perror("  accept() failed");
                                    //TODO: endserver
                                    //end_server = TRUE;
                                }
                                break;
                            }


                            // i > 1 -> connected clients, add client to pollfd structure
                            printf("  New incoming connection - %d\n", new_client_fd);

                            poll_fds[clients_fds_counter].fd = new_client_fd;
                            poll_fds[clients_fds_counter].events = POLLIN;
                            clients_fds_counter++;

                        } while (new_client_fd != -1);
                    }


                    // Work only for connected CLIENTS
                    else {

                        while(1){
                            // Handle  client request
                            request*  req = handle_client_request(poll_fds[i].fd);

                            if(req->bytes_recv_from_client <=0 ){
                                free_client_request(req);
                                close(poll_fds[i].fd);
                                poll_fds[i].fd = -1;
                                break;
                            }

                            free_client_request(req);
                            break;

                        }

                    }
                }

            } while (1); /* End of serving running.    */

    destroy_configuration();
    return (0);
    }

