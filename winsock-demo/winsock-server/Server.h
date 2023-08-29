#include "IServer.h"

#define PORT_NUMBER "55555"
#define DEFAULT_BUFLEN 512

class Server : public IServer {

    private:
        SOCKET clientSocket = INVALID_SOCKET;
        char recvBuf[DEFAULT_BUFLEN];
        int iResult;
        int recvBufLen = DEFAULT_BUFLEN;
        const char *response = "Server response: Message received";

    public:
        void loadWinsockLibrary(void);
        void createHintsForAddress(void);
        void retrieveAddressInfo(void);
        void defineListeningSocket(void);
        void bindSocketToTheNetwork(void);
        void listenForConnection(void);
        void acceptConnection(void);
        void receiveAndSendData(void);
        void shutdownTheServer(void);

};