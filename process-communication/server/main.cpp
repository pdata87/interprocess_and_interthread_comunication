
#include "SocketServer.h"

int main() {
    // port and poll timeout
    SocketServer srv(20000,60);
    srv.start();

    return 0;
}