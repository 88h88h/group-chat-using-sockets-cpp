# Group Chat Using Sockets in C++

This project implements a simple group chat application using sockets in C++. It includes both server and client programs. Multiple clients can connect to the server and send messages to each other in real-time.

## Features

- **Multi-client support**: Multiple clients can connect to the server simultaneously.
- **Real-time messaging**: Clients can send and receive messages in real-time.
- **Threaded handling**: The server uses threads to handle multiple clients concurrently.
- **Simple command interface**: Clients can send messages and exit the chat using a simple interface.

## Prerequisites

- **C++ compiler**: Make sure you have a C++ compiler installed.
- **Winsock library**: The application uses the Winsock2 library for socket programming.

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/yourusername/group-chat-using-sockets-cpp.git
cd group-chat-using-sockets-cpp
```

### Build the Project

Ensure you have Visual Studio or another C++ development environment set up with the Winsock2 library.

- Open the project in your development environment.
- Build the solution.

### Running the Server

- Navigate to the directory containing the server executable.
- Run the server:
 ``` bash
 ./server.exe
```
The server will start listening on port 5000 for incoming client connections.

### Running the Client

- Navigate to the directory containing the server executable.
- Run the client:
 ``` bash
 ./client.exe
```
The server will start listening on port 5000 for incoming client connections.

- Enter your username when prompted.
- Start sending messages. Type quit to exit the chat.

## Example

### Server Output
``` bash
Listening on port: 5000
Client connected
Message from client: user1: Hello
Message from client: user2: Hi there!
Client disconnected
```

### Client Output
```bash
Enter your username: user1
Successfully connected to the server
user2: Hi there!
```

## Acknowledgements

- The Winsock2 library for providing the necessary network functionality.
- The C++ Standard Library for threading support.
