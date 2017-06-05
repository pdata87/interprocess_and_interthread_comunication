//
// Created by pdata on 30.05.17.
//

#include <zconf.h>
#include <algorithm>
#include "ConnectionPoll.h"

Client & ConnectionPoll::addClient(pollfd &clientFD, string identifier) {

    this->pollFDS.push_back(clientFD);
    Client  client(clientFD.fd,identifier);

    if(identifier!="Master") {
        this->connectedClients.insert(make_pair(clientFD.fd,  client ));
    }
    return getClientByFD(clientFD.fd);

}
const vector<pollfd> ConnectionPoll::getClientsPool() {

    return  pollFDS;
}

pollfd *   ConnectionPoll::getMasterFD() {

    return &this->pollFDS[0];
}
ConnectionPoll::ConnectionPoll() {

}

map<int,Client> ConnectionPoll::getConnectedClients() {


    return this->connectedClients;
}

Client & ConnectionPoll::getClientByFD(int fd) {
    return this->connectedClients.find(fd)->second;
}

void ConnectionPoll::closeClientConnection(int clientFD) {

    std::map<int,Client>::iterator clientIterator;
    vector<pollfd>::iterator pollFDIterator;

    removeFromPollFDS(this->pollFDS,clientFD);
    clientIterator = connectedClients.find(clientFD);
    connectedClients.erase(clientIterator);
    close(clientFD);





    vector<pollfd> pollFDS;

}

void ConnectionPoll::removeFromPollFDS(std::vector<pollfd> &pollfds, int fd) {
    pollfds.erase(
            std::remove_if(pollfds.begin(), pollfds.end(), [&](pollfd const & pfd) {
                return pfd.fd == fd;
            }),
    pollfds.end());
}

ConnectionPoll &ConnectionPoll::getInstance() {
    static ConnectionPoll instance;
    return instance;
}

