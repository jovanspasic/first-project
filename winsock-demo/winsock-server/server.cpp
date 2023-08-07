#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#define PORT_NUMBER "55555"
#define DEFAULT_BUFLEN 512

using namespace std;

int main(void) {
    // Loading the Winsock library
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);

    if(WSAStartup(wVersionRequested, &wsaData) != 0) {
        cout << "An error occured while initiating use of Winsock library on the server" << endl;
        return 1;
    }
    cout << "The Winsock library was initiated successfully" << endl;

    // Return the server address and port number 
    struct addrinfo *result = NULL,
                    hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if(getaddrinfo(NULL, PORT_NUMBER, &hints, &result) != 0) {
        cout << "An error occured while trying to retrieve address and port data" << endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    cout << "Retrieving of the data for address and port successful" << endl;

    // Defining a socket for listening
    SOCKET listenSocket = INVALID_SOCKET;
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if(listenSocket == INVALID_SOCKET) {
        cout << "An error occured while trying to trying to create a listening socket" << endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    cout << "Listening socket created successfully" << endl;

    // Binding the socket to the network
    if(bind(listenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        cout << "An error occured while trying to bind the socket" << endl;
        closesocket(listenSocket);
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    cout << "Binding of the socket was finished successfully" << endl;
    freeaddrinfo(result);

    // Listening the socket for client requests
    if(listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "An error occure while trying to listen to the socket" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    cout << "The server is now listening for client requsts" << endl;

    // Accepting a connection from the client
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = accept(listenSocket, NULL, NULL);

    if(clientSocket == INVALID_SOCKET) {
        cout << "An error occured while trying to accept client request" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    cout << "The server is now accepting client requests" << endl;
    closesocket(listenSocket);

    // Receiving data from the client
    char recvBuf[DEFAULT_BUFLEN];
    int iResult;
    int recvBufLen = DEFAULT_BUFLEN;
    const char *response = "Server response: Message received";

    do {
        iResult = recv(clientSocket, recvBuf, recvBufLen, 0);
        if(iResult > 0) {
            cout << "There are " << iResult << " bytes received from the client" << endl;
            cout << "The message received from the client is " << recvBuf << endl;
            if(send(clientSocket, response, strlen(response), 0) == SOCKET_ERROR) {
                closesocket(clientSocket);
                WSACleanup();
                return 1;
            }
            cout << "Message sent successfully" << endl;
        } else if(iResult == 0) {
            cout << "Closing connection" << endl;
        } else {
            cout << "Receiving failed with an error: " << WSAGetLastError() << endl;
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);
    
    // Shutting down the socket
    if(shutdown(clientSocket, SD_SEND) == SOCKET_ERROR) {
        cout << "An error occured while trying to shut the socket down" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}