#include ".\Client\Client.h"

int main(void) {
    Client client;
    client.startClient();
    client.closeClient();

    return 0;
}