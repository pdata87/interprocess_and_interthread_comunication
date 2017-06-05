//
// Created by pdata on 30.05.17.
//

#ifndef PROCESS_COMMUNICATION_CLIENT_H
#define PROCESS_COMMUNICATION_CLIENT_H


#include <poll.h>
#include <string>
using namespace std;

class Client {

    int fd;
    string identifier;
    string ip_addr;


public:

    Client(int fd, string identifier);
    string getClientInfo();
    void setIPaddr(string ip_info);
    void setIdentifier(string indentifier);
    int getFD();

};


#endif //PROCESS_COMMUNICATION_CLIENT_H
