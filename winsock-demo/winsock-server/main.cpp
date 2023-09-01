#include ".\Server\Server.h"

int main(void) {
    Server server;
    server.startServer();
    server.handleMessages();
    server.closeServer();

    return 0;
}