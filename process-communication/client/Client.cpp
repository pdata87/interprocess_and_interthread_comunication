//
// Created by pdata on 30.06.17.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include "Client.h"
Client::Client()
{
    sock = -1;
    port = 0;
    address = "";
}


bool Client::createConnection(string address, int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }

        cout<<"Socket created\n";
    }




    server.sin_addr.s_addr = inet_addr( address.c_str() );
    server.sin_family = AF_INET;
    server.sin_port = htons( port );


    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connection failed");
        return 1;
    }

    cout<<"Connected\n";
    return true;
}


bool Client::sendData(string data)
{
    //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    return true;
}


string Client::receive(int size=512)
{
    char buffer[size];
    string reply;

    //Receive a reply from the server
    if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("recv failed");
    }

    reply = buffer;
    return reply;
}