#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

class IServer {

    protected:
        WSADATA wsaData;
        struct addrinfo *result = NULL;
        SOCKET listenSocket = INVALID_SOCKET;

    public:
        virtual void startServer(void) = 0;
        virtual void handleMessages(void) = 0;
        virtual void closeServer(void) = 0;
        
};