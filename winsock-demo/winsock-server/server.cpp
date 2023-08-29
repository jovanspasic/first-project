#include "Server.h"

void Server::loadWinsockLibrary() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "An error occured while initiating use of Winsock library on the server" << endl;
        exit(1);
    }
    cout << "The Winsock library was initiated successfully" << endl;
}

void Server::createHintsForAddress() {
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
}

void Server::retrieveAddressInfo() {
    if (getaddrinfo(NULL, PORT_NUMBER, &hints, &result) != 0)
    {
        cout << "An error occured while trying to retrieve address and port data" << endl;
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }
    cout << "Retrieving of the data for address and port successful" << endl;

}

void Server::defineListeningSocket() {
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (listenSocket == INVALID_SOCKET)
    {
        cout << "An error occured while trying to trying to create a listening socket" << endl;
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }
    cout << "Listening socket created successfully" << endl;
}

void Server::bindSocketToTheNetwork() {
    if (bind(listenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
    {
        cout << "An error occured while trying to bind the socket" << endl;
        closesocket(listenSocket);
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }
    cout << "Binding of the socket was finished successfully" << endl;
    freeaddrinfo(result);
}

void Server::listenForConnection() {
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "An error occure while trying to listen to the socket" << endl;
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }
    cout << "The server is now listening for client requsts" << endl;
}

void Server::acceptConnection() {
    clientSocket = accept(listenSocket, NULL, NULL);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "An error occured while trying to accept client request" << endl;
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }
    cout << "The server is now accepting client requests" << endl;
    closesocket(listenSocket);
}

void Server::receiveAndSendData() {
    do {

        iResult = recv(clientSocket, recvBuf, recvBufLen, 0);
        if(iResult > 0) {
            cout << "Number of bytes received from the client: " << iResult << endl;
            cout << "Message from the client: " << recvBuf << endl;
            if(send(clientSocket, response, strlen(response) + 1, 0) == SOCKET_ERROR) {
                cout << "An error occured while trying to send the message" << endl;
                closesocket(clientSocket);
                WSACleanup();
                exit(1);
            }
            cout << "Message sent successfully" << endl;
        }

        else if (iResult == 0) {
            cout << "Closing connection" << endl;
        }

        else {
            cout << "Receiving failed with an error: " << WSAGetLastError() << endl;
            closesocket(clientSocket);
            WSACleanup();
            exit(1);
        }

    } while(iResult > 0);
}

void Server::shutdownTheServer() {
    if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR)
    {
        cout << "An error occured while trying to shut the socket down" << endl;
        closesocket(clientSocket);
        WSACleanup();
        exit(1);
    }

    closesocket(clientSocket);
    WSACleanup();
    cout << "The server has been shutdown" << endl;
}