#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>



#define MY_SOCK_PATH "127.0.0.1"

void main() {
    int clientSocket, portno, n,conn;

    struct sockaddr_in server_addr;
    char BUFFER[1024] = "<root><status><if>eth0</if><if>wlan0</if></status><list/><if_address/><if_ip/></root>";

    
    clientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(20000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");




    if(clientSocket<0){
        puts("Error opening socket");

    }

    conn = connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(conn<0){

        puts("Client can't connect");
    }
    else{

        send(clientSocket,BUFFER,sizeof(BUFFER),0);

    }




        perror("Error: ");
        printf("%s", "Finish");
}