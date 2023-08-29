#include "IClient.h"

#define PORT_NUMBER "55555"
#define DEFAULT_BUFLEN 512

class Client : public IClient {

    private:
        int recvBufLen = DEFAULT_BUFLEN;
        char recvBuf[DEFAULT_BUFLEN];
        int iResult;
        const char *message = "Testing 1, 2, 3...";
        string userRequest;

    public:
        void loadWinsockLibrary(void);
        void createHintsForAddress(void);
        void retrieveAddressInfo(void);
        void connectToTheServer(void);
        void sendMesageAndReceiveResponse(void);
        void shutdownTheClient(void);

};