#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

const int MAX_BUFFER_SIZE = 1024;

void sendIRCCommand(int socket, const std::string& command) {
  std::string fullCommand = command + "\r\n";
  send(socket, fullCommand.c_str(), fullCommand.size(), 0);
}

std::string receiveIRCResponse(int socket) {
  char buffer[MAX_BUFFER_SIZE];
  memset(buffer, 0, sizeof(buffer));

  int bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0);
  if (bytesReceived == -1) {
    std::cerr << "Error in receiving data from the server.\n";
    return "";
  }

  return std::string(buffer);
}

int main() {
  const char* serverAddress = "0.0.0.0";
  const char* serverPort = "6677";
  const char* channel = "#your_channel_name";
  const char* nickname = "your_nickname";

  // Creating socket
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    std::cerr << "Error in creating socket.\n";
    return 1;
  }

  // Resolving server address
  struct addrinfo hints, *serverInfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(serverAddress, serverPort, &hints, &serverInfo) != 0) {
    std::cerr << "Error in resolving server address.\n";
    close(clientSocket);
    return 1;
  }

  // Connecting to the server
  if (connect(clientSocket, serverInfo->ai_addr, serverInfo->ai_addrlen) ==
      -1) {
    std::cerr << "Error in connecting to the server.\n";
    close(clientSocket);
    freeaddrinfo(serverInfo);
    return 1;
  }
  std::cout << "connected to server!\n";

  freeaddrinfo(serverInfo);

  // Send NICK and USER commands to login to the server
  sendIRCCommand(clientSocket, "NICK " + std::string(nickname));
  sendIRCCommand(clientSocket, "USER " + std::string(nickname) +
                                   " 0 0 :" + std::string(nickname));

  // Join the channel
  sendIRCCommand(clientSocket, "JOIN " + std::string(channel));

  // Send PRIVMSG command
  std::string message = "/PRIVMSG " + std::string(channel) + " :Hello";
  sendIRCCommand(clientSocket, message);

  // Receive and print the response
  std::string response = receiveIRCResponse(clientSocket);
  std::cout << "Server response: " << response << std::endl;

  // Close the socket
  close(clientSocket);

  return 0;
}
