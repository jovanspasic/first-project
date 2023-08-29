#include "Client.h"

int main(void) {
    Client client;
    client.loadWinsockLibrary();
    client.createHintsForAddress();
    client.retrieveAddressInfo();
    client.connectToTheServer();
    client.sendMesageAndReceiveResponse();
    client.shutdownTheClient();

    return 0;
}