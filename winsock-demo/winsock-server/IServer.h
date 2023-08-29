#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

class IServer
{

    protected:
        WSADATA wsaData;
        struct addrinfo *result = NULL;
        struct addrinfo hints;
        SOCKET listenSocket = INVALID_SOCKET;

    public:
        virtual void loadWinsockLibrary(void) = 0;
        virtual void createHintsForAddress(void) = 0;
        virtual void retrieveAddressInfo(void) = 0;
        virtual void defineListeningSocket(void) = 0;
        virtual void bindSocketToTheNetwork(void) = 0;
        virtual void listenForConnection(void) = 0;
        virtual void acceptConnection(void) = 0;
        virtual void receiveAndSendData(void) = 0;
        virtual void shutdownTheServer(void) = 0;
};