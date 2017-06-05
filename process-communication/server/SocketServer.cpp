//
// Created by pdata on 30.05.17.
//

#include <cstdio>
#include <string>
#include <iostream>
#include <zconf.h>
#include <arpa/inet.h>
#include <cstring>
#include "SocketServer.h"
#include "ConnectionPoll.h"
#include "Message.h"

void SocketServer::handleClientMessage(string clientMessage, Client & sender, bool toAll) {
    Message m (clientMessage,sender);



    if(toAll){

        for(auto client : ConnectionPoll::getInstance().getConnectedClients()){

            if(client.first != sender.getFD()){

                string serverMessage  = m.getMessage();
                send(client.first,serverMessage.c_str(),serverMessage.length(),0);
            }

        }


    }



}
bool SocketServer::setupSocket(int port){
    this->serverFD =  createSocket();
    int reuse = 1;
    setsockopt(this->serverFD,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    bindAndListen();
    createPoll(this->serverFD);



}
SocketServer::SocketServer(int listeningPort, int maxConn) {

    remote_addr_size = sizeof client_addr;
    maxConnections=maxConn;
    port=listeningPort;
    setupSocket(port);
}
SocketServer::~SocketServer() {
    this->pollTimeOut = 60000;
}
void SocketServer::start() {



    while(true){
        pollfd *  masterFD = ConnectionPoll::getInstance().getMasterFD();

        poll(masterFD, (nfds_t) ConnectionPoll::getInstance().getClientsPool().size(), this->pollTimeOut);



        if(masterFD->revents & POLLIN){

            int newClientFd = accept(masterFD->fd,(struct sockaddr *)&client_addr,&remote_addr_size);
            pollfd clientPollStructure = pollfd();

            clientPollStructure.fd = newClientFd;
            clientPollStructure.events = POLLIN;


            ConnectionPoll::getInstance()
                    .addClient(clientPollStructure).
                    setIPaddr(inet_ntoa(client_addr.sin_addr));


            sendWelcomeMessage(newClientFd);


        }
        else {

            for (auto currentClientPoll : ConnectionPoll::getInstance().getClientsPool() ){

                if( currentClientPoll.revents & POLLIN){
                    std::vector<char> buffer(4096);
                    string recivedData = "";

                    int recv_bytes = recv(currentClientPoll.fd,buffer.data(),buffer.size(),0);
                        if(recv_bytes > 0){

                            recivedData.append(buffer.cbegin(),buffer.cend());
                            handleClientMessage(recivedData, ConnectionPoll::getInstance().getClientByFD(currentClientPoll.fd));
                            buffer.erase(buffer.begin(),buffer.end());
                            recivedData.clear();
                        }

                    if(recv_bytes == 0) {
                        //TODO : Add disconnect client to clients poll.
                        ConnectionPoll::getInstance().closeClientConnection(currentClientPoll.fd);
                    }



                }

            }

        }

    }
}
int SocketServer::createSocket() {

    this->sockAddr.sin_port = htons(port);
    this->sockAddr.sin_family = AF_INET;
    this->sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    return socket(AF_INET,SOCK_STREAM,0);
}
void SocketServer::bindAndListen() {
    int operationResult =     bind(this->serverFD,(struct sockaddr *)&sockAddr,sizeof(sockAddr));
    if(operationResult < 0){
        perror("Operation didnt succeedd");
        exit(-1);
    }
    listen(this->serverFD,maxConnections);
}
void SocketServer::createPoll(int socketFD) {
    pollfd master;
    master.fd= socketFD;
    master.events=POLLIN;
    ConnectionPoll::getInstance().addClient(master,"Master");
}

void SocketServer::sendWelcomeMessage(int newClientFd) {

    string welcomeText("Now you can write to others.\r\n If you want to please type: name=your_name to set up your identifier \r\n");
    send(newClientFd,welcomeText.c_str(),welcomeText.length(),0);
}
