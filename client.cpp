#include <iostream>
#include <Winsock2.h>
#include <ws2tcpip.h>

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

    // send/recv
    string message = "hello there!";
    int bytesent;
    bytesent = send(s, message.c_str(), message.length(), 0);

    if (bytesent == SOCKET_ERROR)
    {
        cout << "send failed: " << WSAGetLastError() << endl;
    }

    closesocket(s);

    WSACleanup();
    return 0;
}