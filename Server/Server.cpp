#include "Server.hpp"

#include <iostream>  // delete

#include "../Client/Client.hpp"
#include "../RequestHandler/RequestHandler.hpp"

Server::Server(char *port, char *password) : _port(port), _password(password) {
  (void)_password;  // 임시
}

void Server::init_tmp() {
  _serverFd = socket(PF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(_port));
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(_serverFd, reinterpret_cast<struct sockaddr *>(&serverAddr),
           sizeof(serverAddr)) == -1) {
    Close(_serverFd);  // Fail
    throw std::runtime_error("bind error");
  }
  std::cout << "addr: " << inet_ntoa(serverAddr.sin_addr) << "\n";
  listen(_serverFd, FD_MAX);
  FD_ZERO(&_readSet);
  FD_SET(_serverFd, &_readSet);
}

void Server::init() {
  // 가능한 서버 주소 리스트 받아오기
  struct addrinfo sockOpt, *sockAddrList, *iter;
  memset(&sockOpt, 0, sizeof(struct addrinfo));
  sockOpt.ai_socktype = SOCK_STREAM;              // Accept TCP connections
  sockOpt.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;  // 시스템에서 사용 가능한 IP만
  sockOpt.ai_flags |= AI_NUMERICSERV;  // port 번호를 숫자로 지정하도록
  Getaddrinfo(NULL, _port, &sockOpt, &sockAddrList);

  // 그 리스트에서 우리가 bind할 하나를 찾음
  for (iter = sockAddrList; iter; iter = iter->ai_next) {
    // socket descriptor 생성
    _serverFd = Socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
    if (_serverFd < 0) {
      continue;
    }
    // SO_REUSEADDR - 이전에 사용된 주소와 포트를 빠르게 재사용할 수 있도록 함
    // bind에서 발생할 수 있는 "Address already in use" error 제거
    int optval = 1;
    std::cout << "serverfd: " << _serverFd << "\n";
    Setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
               sizeof(int));
    // 만든 socket descriptor를 address에 bind
    if (Bind(_serverFd, iter->ai_addr, iter->ai_addrlen) == 0) {
      break;  // Success
    }
    Close(_serverFd);  // Fail
    FD_ZERO(&_readSet);
    FD_SET(_serverFd, &_readSet);
  }

  freeaddrinfo(sockAddrList);
  if (!iter) {
    throw std::runtime_error("No address found");
  }
  listen(_serverFd, FD_MAX);
}

void Server::run() {
  int tmp = 0;
  init_tmp();
  int fdCount = _serverFd;
  std::cout << "serverFd: " << _serverFd << "\n";
  int clientFd = -1;
  // TODO: timeout
  struct timeval timeout;
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;

  while (true) {
    _readySet = _readSet;
    // TODO: select wrapper
    tmp = select(fdCount + 1, &_readySet, 0, 0, &timeout);
    if (tmp == -1) {
      throw std::runtime_error("select error");
    }
    if (tmp == 0) {
      std::cout << "timeout!\n";
      continue;
    }
    for (int i = 0; i <= fdCount; i++) {
      if (FD_ISSET(i, &_readySet)) {
        // accept
        // server 소켓
        if (i == _serverFd) {
          sockaddr_in client_addr;
          socklen_t client_addr_len = sizeof(client_addr);
          clientFd = accept(_serverFd,
                            reinterpret_cast<struct sockaddr *>(&client_addr),
                            &client_addr_len);
          if (clientFd == -1) throw std::runtime_error("accept failed");
          // _clientFds[clientFd] = new Client(clientFd);
          FD_SET(clientFd, &_readSet);
          if (fdCount < clientFd) fdCount = clientFd;
        }
        // client 솤
        else {
          char buffer[512];
          // TODO: recv wrapper
          int receivedBytes = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
          if (receivedBytes == 0) {
            memset(buffer, 0, sizeof(buffer));
            continue;
          }
          if (receivedBytes < 0) {
            throw std::runtime_error("recv error");
          }
          std::cout << "recv: " << buffer << std::endl;  // check recv
          RequestHandler requesthandler(clientFd, buffer);
          requesthandler.execute();
        }
        // TODO : getnameinfo (허용함수 아님, 찾아보기)
      }
    }
  }
}

void Server::Getaddrinfo(const char *node, const char *service,
                         const struct addrinfo *hints, struct addrinfo **res) {
  if (getaddrinfo(node, service, hints, res) != 0) {
    throw std::runtime_error("Getaddrinfo error");
  }
}

int Server::Socket(int domain, int type, int protocol) {
  int val = socket(domain, type, protocol);
  if (val == -1) {
    throw std::runtime_error("Socket error");
  }
  return val;
}

void Server::Setsockopt(int s, int level, int optname, const void *optval,
                        int optlen) {
  if (setsockopt(s, level, optname, optval, optlen) < 0) {
    throw std::runtime_error("Setsockopt error");
  }
}

int Server::Bind(int sockfd, struct sockaddr *my_addr, int addrlen) {
  int val = bind(sockfd, my_addr, addrlen);
  if (val == -1) {
    throw std::runtime_error("Bind error");
  }
  return val;
}

void Server::Close(int fd) {
  if (close(fd) < 0) {
    throw std::runtime_error("Close error");
  }
}

void Server::Listen(int sockfd, int backlog) {
  if (listen(sockfd, backlog) < 0) {
    Close(sockfd);
    throw std::runtime_error("Listen error");
  }
}
