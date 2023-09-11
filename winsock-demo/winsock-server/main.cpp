#include ".\Server\Server.h"

int main(void) {
    Server server;
    thread tr1([]{ServerLogger::getInstance().storeLogMessage();});

    server.startServer();
    server.closeServer();

    tr1.join();

    return 0;
}