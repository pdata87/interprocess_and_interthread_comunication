#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <error.h>
#include <unistd.h>

#define MY_SOCK_PATH "/tmp/socket/s"
void main() {
    int sockfd, portno, n,conn;

    struct sockaddr server_addr = {AF_UNIX, MY_SOCK_PATH};
    char BUFFER[1024];


    sockfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sockfd<0){
        puts("Error opening socket");

    }

    conn = connect(sockfd, &server_addr, sizeof(server_addr));
    if(conn<0){


    }else{
        puts("Client connected");
        read(sockfd,BUFFER,1024);
        printf("%s", BUFFER);

    }





        printf("%s", "Finish");
}