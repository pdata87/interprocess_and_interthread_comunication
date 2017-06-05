//
// Created by pdata on 30.05.17.
//

#include "Message.h"
#include <ctime>
#include <cstring>
#include <iostream>

using namespace std;
using namespace chrono;

Message::Message(string messageText, Client & sender) :  sender(sender) {

    this->receiveTime = system_clock::to_time_t(system_clock::now());
    time(&(this->receiveTime));

    string clientInfo = sender.getClientInfo();


    //TODO: Move this code to another class ex: MessageCommand
    if(messageText.find("name=") == 0){
        int index =    (int)messageText.find("=") + 1;
        string name  =messageText.substr(index,messageText.size());
        sender.setIdentifier(name);
        this->messageBody = clientInfo.append(" has changed his name to ").append(name);
cd .
    }
    else {
        this->messageBody = messageText;
    }



}

string Message::getMessage() {

    string output("\r\nMessage received on server at : ");
    output.append(ctime(&this->receiveTime));
    output.append("\r\n");
    output.append("Client information : ");
    output.append(this->sender.getClientInfo());
    output.append("\r\n");
    output.append("Message body  : ");
    output.append(this->messageBody);

    return output;

}

void Message::setMessage(string msgTxt) {
    this->messageBody = msgTxt;
}
