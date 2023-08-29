#include "Server.h"

int main(void) {
    Server server;
    server.loadWinsockLibrary();
    server.createHintsForAddress();
    server.retrieveAddressInfo();
    server.defineListeningSocket();
    server.bindSocketToTheNetwork();
    server.listenForConnection();
    server.acceptConnection();
    server.receiveAndSendData();
    server.shutdownTheServer();

    return 0;
}