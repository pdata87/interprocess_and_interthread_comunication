//
// Created by pdata on 30.05.17.
//

#include "Client.h"


Client::Client(int fd, string identifier="anonymous") {

    this->fd = fd;
    this->identifier = identifier;
}

string Client::getClientInfo() {
    string output;

    output.append("Client IP : ").append(this->ip_addr).append("\r\n");

    output.append("\t Client id : ").append(this->identifier).append("\r\n");

    return output;
}

void Client::setIPaddr(string ip_info) {

    ip_addr=ip_info;
}

int Client::getFD() {

    return this->fd;
}

void Client::setIdentifier(string id) {
    this->identifier = id;

}
