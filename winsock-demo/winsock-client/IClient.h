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
        virtual void loadWinsockLibrary(void) = 0;
        virtual void createHintsForAddress(void) = 0;
        virtual void retrieveAddressInfo(void) = 0;
        virtual void connectToTheServer(void) = 0;
        virtual void sendMesageAndReceiveResponse(void) = 0;
        virtual void shutdownTheClient(void) = 0;

};