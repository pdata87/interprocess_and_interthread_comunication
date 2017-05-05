#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <zconf.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include "command_parser.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TRUE             1
#define FALSE            0

// this function parses data sent by client
int  handle_client_data(int client_fd) {
    char buffer[1024] ="";
    int data_size = -1;
    data_size = recv(client_fd, buffer, sizeof(buffer), 0);

    switch(data_size){
        default:
            parse_client_input(buffer);
        case -1 :
            perror("Failed to receive DATA from client: ");
            break;
        case 0 :
            printf(" Connection closed by client\n");
            close(client_fd);
            break;

    }

    return data_size;
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
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(20000);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    close_conn = FALSE;


    listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

        return_value = listen(listeningSocket, 50);
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
                        printf("  Descriptor %d is readable\n", poll_fds[i].fd);
                        // TODO close connection
                        //close_conn = FALSE;


                        while(TRUE){
                            // Handle  client data
                            return_value = handle_client_data(poll_fds[i].fd);

                            if (return_value < 0) {
                                if (errno != EWOULDBLOCK) {
                                    perror("  recv() failed");
                                    close_conn = TRUE;
                                }

                                break;
                            }

                            printf("Bytes send by client : %d",return_value);
                            
                            // TODO function which return output to client
                            // send some data to client
                            return_value = send(poll_fds[i].fd, "Server response here", 20, 0);
                            if (return_value < 0) {
                                perror("  send() failed");
                                // TODO Why connection was closed ?
                                close_conn = TRUE;
                                break;
                            }
                            break;

                        }


                        //TODO: Handle closing connection
                        if (close_conn) {
                            close(poll_fds[i].fd);
                            poll_fds[i].fd = -1;

                        }


                    }
                }


                //TODO: Defeine when server should be terminated
            } while (1); /* End of serving running.    */

        return (0);
    }

