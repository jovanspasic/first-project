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
        cout << "An error occured while initiating use of Winsock library on the client" << endl;
        return 1;
    }
    cout << "The Winsock library was initiated successfully" << endl;

    // Resolve server address and port
    struct addrinfo *result = NULL,
                    hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if(getaddrinfo("localhost", PORT_NUMBER, &hints, &result) != 0) {
        cout << "An error occured while trying to resolve servers address and port" << endl;
        WSACleanup();
        return 1;
    }
    cout << "Resolving server address and port successful" << endl;

    // Creating a socket 
    SOCKET connectSocket = INVALID_SOCKET;
    connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if(connectSocket == INVALID_SOCKET) {
        cout << "An error occured while trying to create a socket for the client" << endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    cout << "Connection socket created successfully" << endl;

    // Connecting to the server
    if(connect(connectSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        cout << "Unable to connect to server" << endl;
        closesocket(connectSocket);
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Sending data to the server
    int recvBufLen = DEFAULT_BUFLEN;
    char recvBuf[DEFAULT_BUFLEN];
    int iResult;
    const char *message = "Testing 1, 2, 3...";

    if(send(connectSocket, message, strlen(message), 0) == SOCKET_ERROR) {
        cout << "There was an error while trying to send the message to the server" << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    cout << "The message was sent to the server" << endl;

    iResult = shutdown(connectSocket, SD_SEND);
    if(iResult == SOCKET_ERROR) {
        cout << "An error occured while trying to shut the socket down" << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    do {
        iResult = recv(connectSocket, recvBuf, recvBufLen, 0);
        if(iResult > 0) {
            cout << "Data received from the server" << endl;
            cout << "The message received from the server is " << recvBuf << endl;
        } else if(iResult == 0) {
            cout << "Closing connection" << endl;
        } else {
            cout << "Receiving failed with an error: " << WSAGetLastError() << endl;
            closesocket(connectSocket);
            WSACleanup();
            return 1;
        }

    } while(iResult > 0);

    // Shuttin down the socket
    closesocket(connectSocket);
    WSACleanup();

    return 0;
}