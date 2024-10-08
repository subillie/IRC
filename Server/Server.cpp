#include "Server.hpp"

#include "../Client/Client.hpp"
#include "../RequestHandler/Messenger/Messenger.hpp"
#include "../RequestHandler/RequestHandler.hpp"

Server::Server(int port, char *password) : _port(port), _password(password) {
  time_t now;
  time(&now);
  _serverCreated = ctime(&now);
}

Server::~Server() {
  std::map<int, Client *>::iterator client;
  for (client = Server::_clientFds.begin(); client != Server::_clientFds.end();
       ++client) {
    close(client->second->getFd());
    delete (client->second);
    client->second = NULL;
  }
  Server::_clientFds.clear();
  Server::_clientNicks.clear();
  std::map<std::string, Channel *>::iterator channel;
  for (channel = Server::_channelNames.begin();
       channel != Server::_channelNames.end(); ++channel) {
    delete (channel->second);
    channel->second = NULL;
  }
  Server::_channelNames.clear();
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
  Listen(_serverFd, FD_SETSIZE);
  FD_ZERO(&_readSet);
  FD_ZERO(&_writeSet);
  FD_SET(_serverFd, &_readSet);
}

void Server::run() {
  init();

  int fdCount = _serverFd;
  int clientFd = -1;

  while (true) {
    fd_set read = _readSet;
    fd_set write = _writeSet;
    Select(fdCount + 1, &read, &write, 0, 0);

    // Accept connection and handle client's requirements
    for (int i = 0; i <= fdCount; i++) {
      if (FD_ISSET(i, &read)) {
        // Accept connection of a new client
        if (i == _serverFd && _clientFds.size() <= FD_SETSIZE) {
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
          char recvBuffer[512];
          memset(recvBuffer, 0, sizeof(recvBuffer));
          Client *client = _clientFds[i];
          if (recv(i, recvBuffer, sizeof(recvBuffer), 0) <= 0) {
            printRed("Client closed");
            deleteClient(i);
            continue;
          }
          client->buffer += recvBuffer;
          printDebug("buffer", client->buffer);  // Print buffer for debug
          parse(client->buffer);

          while (!_requests.empty()) {
            RequestHandler requestHandler(_clientFds[i], _requests.front(),
                                          _password);
            _requests.pop();
            requestHandler.execute();
            // WriteSet에 전송할 fd추가
            _writeSet = updateWriteSet(
                _writeSet, requestHandler.getMsgWriteSet(), fdCount);
            // Quit 명령어 들어왔을 때 readSet 제거
            if (_clientFds[i]->getIsQuit())
              if (FD_ISSET(i, &_readSet)) FD_CLR(i, &_readSet);
          }
          memset(recvBuffer, 0, sizeof(recvBuffer));
        }
      }
      if (FD_ISSET(i, &write)) {
        try {
          Client *writeClient = _clientFds[i];
          writeClient->sendReplies();   // Client에 저장된 replies를 전송
        } catch (const int fdToQuit) {  // Check send error
          deleteClient(fdToQuit);
        }
        FD_CLR(i, &_writeSet);
      }
    }
  }
}

void Server::parse(std::string &buffer) {
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
  if (FD_ISSET(fd, &_readSet)) FD_CLR(fd, &_readSet);
  Close(fd);
  Client *client = _clientFds[fd];

  // 가입한 모든 채널에서 나가기
  std::set<std::string> channels = client->getChannels();
  std::string nick = client->getNickname();
  for (std::set<std::string>::iterator it = channels.begin();
       it != channels.end(); it++) {
    Channel *channel = Server::_channelNames[*it];
    client->leaveChannel(channel);
  }
  // server의 client 목록에서 삭제
  if (_clientNicks.find(nick) != _clientNicks.end()) {
    _clientNicks.erase(nick);
  }
  delete (client);
  client = NULL;
  _clientFds.erase(fd);
}

fd_set Server::updateWriteSet(fd_set mainSet, fd_set writeSet, int fds) {
  fd_set newWriteSet = mainSet;
  for (int i = 0; i <= fds; i++) {
    if (FD_ISSET(i, &writeSet) && !FD_ISSET(i, &newWriteSet)) {
      FD_SET(i, &newWriteSet);
    }
  }
  return (newWriteSet);
}
