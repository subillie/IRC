#include "Server.hpp"

#include "../Client/Client.hpp"
#include "../RequestHandler/Messenger/Messenger.hpp"
#include "../RequestHandler/RequestHandler.hpp"

Server::Server(int port, char *password) : _port(port), _password(password) {}

Server::~Server() {
  std::map<int, Client *>::iterator client;
  for (client = Server::_clientFds.begin(); client != Server::_clientFds.end();
       ++client) {
    close(client->second->getFd());
    delete (client->second);
  }
  Server::_clientFds.clear();
  Server::_clientNicks.clear();
  std::map<std::string, Channel *>::iterator channel;
  for (channel = Server::_channelNames.begin();
       channel != Server::_channelNames.end(); ++channel) {
    delete (channel->second);
  }
  Server::_channelNames.clear();
  std::cout << "Size of Client Fd Map after deletion: "
            << Server::_clientFds.size() << std::endl;
  std::cout << "Size of Client Nick Map after deletion: "
            << Server::_clientNicks.size() << std::endl;
  std::cout << "Size of Channel Name Map after deletion: "
            << Server::_channelNames.size() << std::endl;
}

void Server::init() {
  _serverFd = Socket(PF_INET, SOCK_STREAM, 0);
  int flags = Fcntl(_serverFd, F_GETFL, 0);
  Fcntl(_serverFd, F_SETFL, flags | O_NONBLOCK);

  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(struct sockaddr_in));
  serverAddr.sin_family = AF_INET;  // IPv4
  serverAddr.sin_port = htons(_port);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  Setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR);
  Bind(_serverFd, reinterpret_cast<struct sockaddr *>(&serverAddr),
       sizeof(serverAddr));
  Listen(_serverFd, FD_MAX);
  FD_ZERO(&_readSet);
  FD_SET(_serverFd, &_readSet);
}

void Server::run() {
  init();

  int fdCount = _serverFd;
  int clientFd = -1;
  // TODO: timeout
  struct timeval timeout;
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;

  while (true) {
    _readySet = _readSet;
    if (Select(fdCount + 1, &_readySet, 0, 0, &timeout) == 0) {
      // std::cout << "Timeout!" << std::endl;
      continue;
    }
    // Accept connection and handle client's requirements
    for (int i = 0; i <= fdCount; i++) {
      if (FD_ISSET(i, &_readySet)) {
        // Accept connection of a new client
        if (i == _serverFd && _clientFds.size() <= FD_MAX) {
          sockaddr_in clientAddr;
          socklen_t clientAddrLen = sizeof(clientAddr);
          clientFd = Accept(_serverFd,
                            reinterpret_cast<struct sockaddr *>(&clientAddr),
                            &clientAddrLen);
          printPikachu();
          printHi();
          addClient(clientFd);  // client 할당
          if (fdCount < clientFd) {
            fdCount = clientFd;
          }
          // Handle requirements of 기존 client
        } else {
          char buffer[512];
          memset(buffer, 0, sizeof(buffer));
          if (Recv(i, buffer, sizeof(buffer), 0) == 0) {
            printRed("Client closed");
            deleteClient(i);
            --fdCount;
            continue;
          }
          printDebug("buffer", buffer);  // TODO: delete
          parse(buffer);
          try {
            while (!_requests.empty()) {
              RequestHandler requestHandler(_clientFds[i], _requests.front(),
                                            _password);
              _requests.pop();
              requestHandler.execute();
            }
          } catch (const char *quit) {
            printRed(quit);
            deleteClient(i);
            --fdCount;
          }
          memset(buffer, 0, sizeof(buffer));
        }
      }
    }
  }
}

void Server::parse(std::string buffer) {
  size_t found = buffer.find("\r\n");
  while (found != std::string::npos) {
    _requests.push(buffer.substr(0, found));
    buffer.erase(0, found + 2);
    found = buffer.find("\r\n");
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

void Server::sendToAllClients(Messenger msg) {
  for (std::map<int, Client *>::const_iterator it = _clientFds.begin();
       it != _clientFds.end(); it++) {
    Messenger copy(msg);
    const int &fd = it->first;
    copy.sendToClient(fd);
  }
}