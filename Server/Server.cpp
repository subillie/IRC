#include "Server.hpp"

#include <iostream>  // delete

#include "../Client/Client.hpp"
#include "../RequestHandler/RequestHandler.hpp"

Server::Server(int port, char *password) : _port(port), _password(password) {}

void Server::init() {
  _serverFd = Socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(struct sockaddr_in));
  serverAddr.sin_family = AF_INET;  // IPv4
  serverAddr.sin_port = htons(_port);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  Bind(_serverFd, reinterpret_cast<struct sockaddr *>(&serverAddr),
       sizeof(serverAddr));
  Listen(_serverFd, FD_MAX);
  FD_ZERO(&_readSet);
  FD_SET(_serverFd, &_readSet);
}

void Server::run() {
  init();

  int fdCount = _serverFd;
  std::cout << "serverFd: " << _serverFd << "\n";
  int clientFd = -1;
  // TODO: timeout
  struct timeval timeout;
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;

  while (true) {
    _readySet = _readSet;
    // TODO : ping
    if (Select(fdCount + 1, &_readySet, 0, 0, &timeout) == 0) {
      std::cout << "Timeout!" << std::endl;
      continue;
    }
    // Accept connection and handle client's requirements
    for (int i = 0; i <= fdCount; i++) {
      // Accept connection of a new client
      if (FD_ISSET(i, &_readySet)) {
        if (i == _serverFd && _clientFds.size() <= FD_MAX) {
          sockaddr_in clientAddr;
          socklen_t clientAddrLen = sizeof(clientAddr);
          clientFd = Accept(_serverFd,
                            reinterpret_cast<struct sockaddr *>(&clientAddr),
                            &clientAddrLen);
          addClient(clientFd);  // client 할당
          if (fdCount < clientFd) {
            fdCount = clientFd;
          }
        }
        // Handle requirements of 기존 client
        else {
          char buffer[512];
          memset(buffer, 0, sizeof(buffer));
          if (Recv(clientFd, buffer, sizeof(buffer), 0) == 0) {
            std::cout << "client Fd: " << clientFd << "\n";
            deleteClient(clientFd);
            continue;
          }
          RequestHandler requestHandler(clientFd, buffer);
          requestHandler.execute();
          memset(buffer, 0, sizeof(buffer));
        }
      }
    }
  }
}

void Server::addClient(int fd) {
  _clientFds[fd] = new Client(fd);
  FD_SET(fd, &_readSet);
}

void Server::deleteClient(int fd) {
  Close(fd);
  FD_CLR(fd, &_readSet);

  Client *client = _clientFds[fd];
  std::string nick = client->getNickname();
  if (_clientNicks.find(nick) != _clientNicks.end()) {
    _clientNicks.erase(nick);
  }
  delete (client);
  _clientFds.erase(fd);
}
