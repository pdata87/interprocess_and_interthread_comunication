//
// Created by pdata on 30.05.17.
//

#ifndef PROCESS_COMMUNICATION_MESSAGE_H
#define PROCESS_COMMUNICATION_MESSAGE_H


#include <ctime>
#include <string>
#include <chrono>
#include "Client.h"

using namespace std;
using namespace chrono;

class Message {


    time_t receiveTime;
    time_t sendTime;
    string messageBody;
    Client sender;

public :
    Message(string messageText, Client & sender);
    string getMessage();
    void setMessage(string msgTxt);

};


#endif //PROCESS_COMMUNICATION_MESSAGE_H
