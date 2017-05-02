#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <zconf.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "command_parser.h"

void handleClient(int c_socket){
    char buffer[1024];
    int i = 0;
    int dataRecived = -1;
    if((dataRecived=recv(c_socket,buffer,sizeof(buffer),0))<0){

        perror("Failed to receive DATA from client: ");
    }
    parse_client_input(buffer);
    close(c_socket);
}




int main(){
    // Change to tcp ip sockets
    int serverSocket, clientSocket,addrLen,fileCheck;
    struct sockaddr_in srv_addr,client_addr;

    addrLen =sizeof(client_addr);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port=htons(20000);
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    char clientAddr[100];


    serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (serverSocket==-1){
        printf("%s\n", "Couldnt create socket");
    }


    if (bind(serverSocket,(struct sockaddr *)&srv_addr,sizeof(struct sockaddr_in))==-1){
        perror("Error: ");
        printf("%s\n", "Couldnt bind to");

    }

    if (listen(serverSocket,50)<0){
        puts("Failed to listen");
    }
    else{
        puts("Waiting for clients");

        while(1){
            clientSocket = accept(serverSocket,(struct sockaddr *)&client_addr,&addrLen);
            if(clientSocket < 0){
                perror("Error: ");
                puts("Failed to accept client connection");
            }
            else{
                puts("Client has been accepted");

                inet_ntop(AF_INET, &(client_addr.sin_addr), clientAddr,100);
                puts(clientAddr);
                handleClient(clientSocket);
            }

        }

    }




    return (0);
}
