//
// Created by pdata on 30.05.17.
//

#include <cstdio>
#include <string>
#include <iostream>
#include "SocketServer.h"

void SocketServer::broadCoastMessage(bool toAll) {
    string message = "test";

    for(auto fd : this->fileDescriptors){
        if(fd.fd!=serverPollFd.fd){
            send(fd.fd,message.c_str(),message.length(),0);
        }

    }
}
bool SocketServer::setupSocket(int port){

    createSocket();
    bindAndListen();
    createPoll();
    serverLoop();


}
SocketServer::SocketServer(int listeningPort) {
    port=listeningPort;
    setupSocket(port);
}
SocketServer::~SocketServer() {

}
void SocketServer::serverLoop() {
    while(true){

        poll( &fileDescriptors[0], (nfds_t) fileDescriptors.size(), 60000 );
        remote_addr_size = sizeof remote_addr;
        if(this->fileDescriptors[0].revents & POLLIN){
            int conn_socket = accept(this->serverFd,(struct sockaddr *)&remote_addr,&remote_addr_size);
            newPollFd.fd=conn_socket;
            newPollFd.events= POLLOUT;
            fileDescriptors.push_back((newPollFd));

            broadCoastMessage(true);
        }
    }
}
void SocketServer::createSocket() {

    this->sockAddr.sin_port = htons(port);
    this->sockAddr.sin_family = AF_INET;
    this->sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->serverFd = socket(AF_INET,SOCK_STREAM,0);
}
void SocketServer::bindAndListen() {
    bind(this->serverFd,(struct sockaddr *)&sockAddr,sizeof(sockAddr));
    listen(this->serverFd,20);
}
void SocketServer::createPoll() {
    this->serverPollFd.fd = serverFd;
    this->serverPollFd.events == POLLIN;
    this->fileDescriptors.push_back(serverPollFd);
}