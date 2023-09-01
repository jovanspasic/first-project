#include "..\Interface\IClient.h"

#define PORT_NUMBER "55555"
#define DEFAULT_BUFLEN 512

class Client : public IClient {

    private:
        int recvBufLen = DEFAULT_BUFLEN;
        char recvBuf[DEFAULT_BUFLEN];
        int iResult;
        string userRequest;

    public:
        void startClient(void);
        void handleRequestsAndResponses(void);
        void closeClient(void);

        void loadWinsockLibrary(void);
        void createHintsForAddress(void);
        void retrieveAddressInfo(void);
        void connectToTheServer(void);
        int sendMessage(void);
        void receiveMessage(void);
        void terminateSession(SOCKET *socket, addrinfo *info);

};