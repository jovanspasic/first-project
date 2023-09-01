#include ".\Client\Client.h"

int main(void) {
    Client client;
    client.startClient();
    client.handleRequestsAndResponses();
    client.closeClient();

    return 0;
}