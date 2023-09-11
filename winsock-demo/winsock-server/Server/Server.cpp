#include "Server.h"

void Server::startServer() {
    loadWinsockLibrary();
    retrieveAddressInfo();
    defineListeningSocket();
    bindSocketToTheNetwork();
    listenForConnection();
    acceptConnection();
    handleMessages();
}

void Server::handleMessages() {
    while(receiveData() == 0) {
        sendData();
    }
}

void Server::closeServer() {
    terminateSession(&clientSocket, NULL);
    serverLogger.log("The server has been shut down", "info");
}

void Server::loadWinsockLibrary() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "An error occured while initiating use of Winsock library on the server" << endl;
        exit(1);
    }
    serverLogger.log("The Winsock library was initiated successfully", "info");
}

void Server::retrieveAddressInfo() {
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, PORT_NUMBER, &hints, &result) != 0) {
        cout << "An error occured while trying to retrieve address and port data" << endl;
        terminateSession(NULL, result);
        exit(1);
    }
    serverLogger.log("Retrieving of the data for address and port successful", "info");
}

void Server::defineListeningSocket() {
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (listenSocket == INVALID_SOCKET) {
        cout << "An error occured while trying to trying to create a listening socket" << endl;
        terminateSession(NULL, result);
        exit(1);
    }
    serverLogger.log("Socket for listening created successfully", "info");
}

void Server::bindSocketToTheNetwork() {
    if (bind(listenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        cout << "An error occured while trying to bind the socket" << endl;
        terminateSession(&listenSocket, result);
        exit(1);
    }
    serverLogger.log("Binding of the socket was finished successfully", "info");
    freeaddrinfo(result);
}

void Server::listenForConnection() {
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "An error occure while trying to listen to the socket" << endl;
        terminateSession(&listenSocket, NULL);
        exit(1);
    }
    serverLogger.log("The server is now listening for client requests", "info");
}

void Server::acceptConnection() {
    clientSocket = accept(listenSocket, NULL, NULL);

    if (clientSocket == INVALID_SOCKET) {
        cout << "An error occured while trying to accept client request" << endl;
        terminateSession(&listenSocket, NULL);
        exit(1);
    }
    serverLogger.log("The server is now accepting client requests", "info");
    closesocket(listenSocket);
}

int Server::receiveData() {
    char recvBuf[DEFAULT_BUFLEN];

    int iResult = recv(clientSocket, recvBuf, DEFAULT_BUFLEN, 0);
    if(iResult > 0) {
        string msg = "Message from the client: ";
        serverLogger.log(msg + recvBuf, "output");
        return 0;
    }

    else if (iResult == 0) {
        serverLogger.log("Closing the connection", "info");
    }

    else {
        cout << "Receiving failed with an error: " << WSAGetLastError() << endl;
        terminateSession(&clientSocket, NULL);
        exit(1);
    }
    return 1;
}

void Server::sendData() {
    const char *response = "Server response: Message received";

    if(send(clientSocket, response, strlen(response) + 1, 0) == SOCKET_ERROR) {
        cout << "An error occured while trying to send the message" << endl;
        terminateSession(&clientSocket, NULL);
        exit(1);
    }
    serverLogger.log("Response sent to the client successfully", "info");
}

void Server::terminateSession(SOCKET *socket, addrinfo *info) {
    if(socket != NULL) {
        closesocket(*socket);
    }
    if(info != NULL) {
        freeaddrinfo(info);
    }
    WSACleanup();
}