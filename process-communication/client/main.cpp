
#include <iostream>
#include "Client.h"


using namespace std;






int main(int argc , char *argv[])
{
    Client c;
    string host;

    cout<<"Enter ip address : ";
    cin>>host;


    c.createConnection(host, 20000);
    cout << "Now you are connected to server (port 20000), please type your messages" << endl;
    string clientData;
    while(1){

        cout<<c.receive(1024);
        cin>>clientData;
        if(clientData =="quit") break;
        c.sendData(clientData);



    }






    return 0;
}