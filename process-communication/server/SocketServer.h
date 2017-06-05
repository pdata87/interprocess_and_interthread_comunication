//
// Created by pdata on 30.05.17.
//

#ifndef PROCESS_COMMUNICATION_SERVER_H
#define PROCESS_COMMUNICATION_SERVER_H
#include <vector>
#include <netinet/in.h>
#include <poll.h>
#include "Client.h"
#include "ConnectionPoll.h"

using namespace std;
class SocketServer {
 public:
    SocketServer(int listeningPort, int maxConn);
    ~SocketServer();
    void start();
    private:
        int port;
        int serverFD;
        int pollTimeOut;
        int maxConnections;



        sockaddr_in sockAddr;
        sockaddr_in client_addr;
        socklen_t remote_addr_size;


    // METHODS

        bool setupSocket(int port);


        int createSocket();
        void bindAndListen();
        void createPoll(int masterFD);

        void sendWelcomeMessage(int newClientFd);



    void handleClientMessage(string clientMessage, Client & sender, bool toAll = true);

};


#endif //PROCESS_COMMUNICATION_SERVER_H
