//
// Created by pdata on 30.05.17.
//

#ifndef PROCESS_COMMUNICATION_SERVER_H
#define PROCESS_COMMUNICATION_SERVER_H
#include <vector>
#include <netinet/in.h>
#include <poll.h>

using namespace std;
class SocketServer {\
 public:
    SocketServer(int listeningPort);
    ~SocketServer();
    private:
        int port;
        vector<pollfd> fileDescriptors;
        pollfd serverPollFd;
        pollfd newPollFd;
        int serverFd;

        sockaddr_in sockAddr;
        sockaddr_storage remote_addr;
        socklen_t remote_addr_size;
    // METHODS
        bool startSever(){}
        bool setupSocket(int port);
        void broadCoastMessage(bool toAll);
        void broadCoastMessage(int clientfd);
        void serverLoop();
        void createSocket();
        void bindAndListen();
        void createPoll();

};


#endif //PROCESS_COMMUNICATION_SERVER_H
