#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

class IClient {

    protected:
        WSADATA wsaData;
        struct addrinfo *result = NULL;
        struct addrinfo *ptr = NULL;
        struct addrinfo hints;
        SOCKET connectSocket = INVALID_SOCKET;

    public:
        virtual void startClient(void) = 0;
        virtual void handleRequestsAndResponses() = 0;
        virtual void closeClient(void) = 0;

};