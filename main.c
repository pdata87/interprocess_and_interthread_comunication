#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <zconf.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>




int main(){
    // Change to tcp ip sockets
    int serverSocket, addrLen,fileCheck;
    struct sockaddr_in srv_addr,client_addr;

    addrLen =sizeof(client_addr);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port=htons(20000);
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);



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

            if(accept(serverSocket,(struct sockaddr *)&client_addr,&addrLen)<0){
                perror("Error: ");
                puts("Failed to accept client connection");
            }
            else{
                puts("Client has been accepted");
            }

        }

    }

//    if(listen(serverSocket,50)== -1){
//      // Wczesniej miałem socket RAW i program nie działał.
//        // mailto : karol.barski@tieto,com
//        //TODO: Nasłuchiwanie wielu klientów
//        printf("%s\n", "Couldnt listen to connection");
//
//    }
//    else {
//        // TODO: nasłuchwianie
//        printf("%s\n", "Listning ...");
//
//        clientSocket = accept(serverSocket,(struct sockaddr *)&peer_addr,sizeof(peer_addr));
//
//
//            if(clientSocket == -1){
//                    printf("%s\n", "Not Accepted");
//
//                }
//            else {
//
//                    printf("%s\n", "Accepted");
//                    write(clientSocket,"test",strlen("test"));
//
//                }
//
//
//
//    }


    return (0);
}
