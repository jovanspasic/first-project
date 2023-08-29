#include "Client.h"

void Client::loadWinsockLibrary() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "An error occured while initiating use of Winsock library on the client" << endl;
        exit(1);
    }
    cout << "The Winsock library was initiated successfully" << endl;
}

void Client::createHintsForAddress() {
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}

void Client::retrieveAddressInfo() {
    if (getaddrinfo("localhost", PORT_NUMBER, &hints, &result) != 0)
    {
        cout << "An error occured while trying to resolve servers address and port" << endl;
        WSACleanup();
        exit(1);
    }
    cout << "Resolving server address and port successful" << endl;
}

void Client::connectToTheServer() {
    for(ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(connectSocket == INVALID_SOCKET) {
            cout << "An error occured while trying to create a socket" << endl;
            WSACleanup();
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
        WSACleanup();
        exit(1);
    }
}

void Client::sendMesageAndReceiveResponse() {

    cout << "Input a message for the server" << endl;
    cin >> userRequest;
    const char *sptr = userRequest.c_str();

    if (send(connectSocket, sptr, strlen(sptr), 0) == SOCKET_ERROR)
    {
        cout << "There was an error while trying to send the message to the server" << endl;
        closesocket(connectSocket);
        WSACleanup();
        exit(1);
    }
    cout << "The message was sent to the server" << endl;


    iResult = shutdown(connectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        cout << "An error occured while trying to shut the socket down" << endl;
        closesocket(connectSocket);
        WSACleanup();
        exit(1);
    }

    do
    {
        iResult = recv(connectSocket, recvBuf, recvBufLen, 0);
        if (iResult > 0)
        {
            cout << "Data received from the server" << endl;
            cout << "The message received from the server is " << recvBuf << endl;
        }
        else if (iResult == 0)
        {
            cout << "Closing connection" << endl;
        }
        else
        {
            cout << "Receiving failed with an error: " << WSAGetLastError() << endl;
            closesocket(connectSocket);
            WSACleanup();
            exit(1);
        }

    } while (iResult > 0);

}

void Client::shutdownTheClient() {
    closesocket(connectSocket);
    WSACleanup();
}