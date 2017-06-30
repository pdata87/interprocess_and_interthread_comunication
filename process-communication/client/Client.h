//
// Created by pdata on 30.06.17.
//
#include <string.h>
#include<iostream>    //cout
#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

using namespace std;

class Client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    Client();
    bool createConnection(string, int);
    bool sendData(string data);
    std::string receive(int);
};


#endif //CLIENT_CLIENT_H
