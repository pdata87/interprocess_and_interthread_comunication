//
// Created by pdata on 30.05.17.
//

#ifndef PROCESS_COMMUNICATION_CONNECTIONPOOL_H
#define PROCESS_COMMUNICATION_CONNECTIONPOOL_H

#include <vector>
#include <map>
#include "Client.h"

using namespace std;
//TODO rewrite to Singleton Class

// this class is responsible for handling client connections
// implemented as Singleton.
class ConnectionPoll {
    private:
    int pollTimeout;
    map<int,Client> connectedClients;
    vector<pollfd> pollFDS;
    void removeFromPollFDS(std::vector<pollfd> &pollfds, int fd);
    public:

        static ConnectionPoll & getInstance();

        Client & addClient(pollfd &clientFD, string identifier = "anonymous");
        map<int, Client> getConnectedClients();
        const vector<pollfd> getClientsPool();
        void closeClientConnection(int clientFD);
        pollfd * getMasterFD();
        Client & getClientByFD(int fd);
    private  :
            ConnectionPoll();
            static ConnectionPoll & Instance;

};


#endif //PROCESS_COMMUNICATION_CONNECTIONPOOL_H
