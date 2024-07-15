#include <iostream>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <thread>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

// Initialize winsock
// create socket
// connect to the server
// send/recv
// close the socket

bool Initialize()
{
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void SendMsg(SOCKET s)
{
    cout << "Enter your username: ";
    string name;
    cin >> name;
    cout << endl;
    string message;

    while (1)
    {
        cin >> message;
        string msg = name + " : " + message;
        int bytesent = send(s, msg.c_str(), static_cast<int>(msg.length()), 0);
        if (bytesent == SOCKET_ERROR)
        {
            cout << "Error sending message " << WSAGetLastError() << endl;
            break;
        }

        if (message == "quit")
        {
            cout << "Stopping the application" << endl;
            break;
        }
    }

    closesocket(s);
    WSACleanup();
}

void ReceiveMsg(SOCKET s)
{
    char buffer[4096];
    int recvlength;
    string msg = "";
    while (1)
    {
        recvlength = recv(s, buffer, sizeof(buffer), 0);
        if (recvlength <= 0)
        {
            cout << "Disconnected from the server" << endl;
            break;
        }
        else
        {
            msg = string(buffer, recvlength);
            cout << msg << endl;
        }
    }

    closesocket(s);
    WSACleanup();
}

int main()
{
    if (!Initialize())
    {
        cout << "winsock initialization failied" << endl;
        return 1;
    }

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    int port = 5000;
    sockaddr_in serveraddr;
    string serveraddress = "127.0.0.1";

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));

    if (connect(s, reinterpret_cast<sockaddr *>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
    {
        cout << "Not able to connect to server: " << WSAGetLastError() << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout << "Successfully connected to the server" << endl;

    thread senderthread(SendMsg, s);
    thread receivethread(ReceiveMsg, s);

    senderthread.join();
    receivethread.join();

    return 0;
}