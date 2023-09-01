#include "..\Interface\IServer.h"
#include "..\Logger\ServerLogger.h"

#define PORT_NUMBER "55555"
#define DEFAULT_BUFLEN 512

class Server : public IServer {

    private:
        SOCKET clientSocket = INVALID_SOCKET;
        char recvBuf[DEFAULT_BUFLEN];
        int iResult;
        int recvBufLen = DEFAULT_BUFLEN;
        const char *response = "Server response: Message received";
        ServerLogger &serverLogger = ServerLogger::getInstance();

    public:
        void startServer(void);
        void handleMessages(void);
        void closeServer(void);

        void loadWinsockLibrary(void);
        void createHintsForAddress(void);
        void retrieveAddressInfo(void);
        void defineListeningSocket(void);
        void bindSocketToTheNetwork(void);
        void listenForConnection(void);
        void acceptConnection(void);
        void sendData(void);
        int receiveData(void);
        void terminateSession(SOCKET *socket, addrinfo *info);

};