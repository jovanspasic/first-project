#include "Client.h"

void Client::startClient() {
    loadWinsockLibrary();
    retrieveAddressInfo();
    connectToTheServer();
    handleRequestsAndResponses();
}

void Client::handleRequestsAndResponses() {
    while(sendMessage() == 0) {
        receiveMessage();
    }
}

void Client::closeClient() {
    terminateSession(&connectSocket, NULL);
}

void Client::loadWinsockLibrary() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "An error occured while initiating use of Winsock library on the client" << endl;
        exit(1);
    }
}

void Client::retrieveAddressInfo() {
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo("localhost", PORT_NUMBER, &hints, &result) != 0) {
        cout << "An error occured while trying to resolve servers address and port" << endl;
        terminateSession(NULL, NULL);
        exit(1);
    }
}

void Client::connectToTheServer() {
    struct addrinfo *ptr = NULL;

    for(ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(connectSocket == INVALID_SOCKET) {
            cout << "An error occured while trying to create a socket" << endl;
            terminateSession(NULL, result);
            exit(1);
        }

        if(connect(connectSocket, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen)) == SOCKET_ERROR) {
            cout << "An error occured while trying to connect to the server" << endl;
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if(connectSocket == INVALID_SOCKET) {
        cout << "An error occured while trying to create a socket" << endl;
        terminateSession(NULL, NULL);
        exit(1);
    }
}

int Client::sendMessage() {
    string userRequest;
    cout << "Input a message for the server" << endl;
    getline(cin, userRequest);

    if(userRequest == "none") {
        cout << "Closing connection" << endl;
        return 1;
    }
    
    const char *sptr = userRequest.c_str();

    if(send(connectSocket, sptr, strlen(sptr) + 1, 0) == SOCKET_ERROR) {
        cout << "An error occured while trying to send a message to the server";
        terminateSession(&connectSocket, NULL);
        exit(1);
    }
    cout << "Message sent successfully" << endl;
    return 0;
}

void Client::receiveMessage() {
    char recvBuf[DEFAULT_BUFLEN];

    int iResult = recv(connectSocket, recvBuf, DEFAULT_BUFLEN, 0);
    if (iResult > 0) {
        cout << "The server responded with: " << recvBuf << endl;
    }
    else if (iResult == 0) {
        cout << "Closing connection" << endl;
    }
    else {
        cout << "Receiving failed with an error: " << WSAGetLastError() << endl;
        terminateSession(&connectSocket, NULL);
        exit(1);
    }
}

void Client::terminateSession(SOCKET *socket, addrinfo *info) {
    if(socket != NULL) {
        closesocket(*socket);
    }
    if(info != NULL) {
        freeaddrinfo(info);
    }
    WSACleanup();
}