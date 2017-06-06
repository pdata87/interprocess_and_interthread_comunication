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

    Message messageObj (clientMessage,sender);

    sendConfirmation((sender.getFD()));

    if(toAll){

        for(auto client : ConnectionPoll::getInstance().getConnectedClients()){

            if(client.first != sender.getFD()){

                string serverMessage  = messageObj.getMessage();
                send(client.first,serverMessage.c_str(),serverMessage.length(),0);
            }
        }
    }
}
bool SocketServer::setupSocket(int port){

    try{
        this->serverFD =  createSocket();
        int reuse = 1;
        setsockopt(this->serverFD,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
        bindAndListen();
        initPoll(this->serverFD);
    }
    catch  (std::string   exception){
        cout << "Socket setup failed  : "  << exception  << endl;
        exit(-1);
    }


}
SocketServer::SocketServer(int listeningPort, int maxConn) {

    remoteaAddrSize = sizeof client_addr;
    maxConnections=maxConn;
    pollTimeOut = 60000;
    port=listeningPort;
    setupSocket(port);
}
SocketServer::~SocketServer() {

}
void SocketServer::start() {



    while(true){
        pollfd *  masterFD = ConnectionPoll::getInstance().getMasterFD();

        poll(masterFD, (nfds_t) ConnectionPoll::getInstance().getClientsPool().size(), pollTimeOut);



        if(masterFD->revents & POLLIN){

            int newClientFd = accept(masterFD->fd,(struct sockaddr *)&client_addr,&remoteaAddrSize);
            pollfd clientPollStructure = pollfd();

            clientPollStructure.fd = newClientFd;
            clientPollStructure.events = POLLIN;


            ConnectionPoll::getInstance()
                    .addClient(clientPollStructure)
                    .setIPAddress(inet_ntoa(client_addr.sin_addr));


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
                        // Close connection with client and remove its data
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

    int operationResult = bind(this->serverFD,(struct sockaddr *)&sockAddr,sizeof(sockAddr));


    if(operationResult < 0){
        std::string exception("Bind didnt succeedd check if port is free");
        throw  exception;

    }
    operationResult = listen(this->serverFD,maxConnections);

    if(operationResult != 0){
        std::string exception("Listen didnt succeedd");
        throw  exception;
    }

}
void SocketServer::initPoll(int socketFD) {
    try {
        pollfd master;
        master.fd= socketFD;
        master.events=POLLIN;
        ConnectionPoll::getInstance().addClient(master,"Master");
    }
    catch(exception e){
        cout <<  e.what() << endl;
        exit(-1);
    }
}

void SocketServer::sendWelcomeMessage(int newClientFd) {

    string welcomeText("Now you can write to others.\r\n If you want to please type: name=your_name to set up your identifier \r\n");
    send(newClientFd,welcomeText.c_str(),welcomeText.length(),0);
}

void SocketServer::sendConfirmation(int clientFD) {
    string confirmation = "Message received by server \r\n";
    send(clientFD,confirmation.c_str(),confirmation.length(),0);

}
