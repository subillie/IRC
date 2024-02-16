#include "Server.hpp"

int Server::Socket(int domain, int type, int protocol) {
  int val = socket(domain, type, protocol);
  if (val == -1) {
    throw std::runtime_error("Socket error");
  }
  return val;
}

int Server::Fcntl(int fd, int cmd, int arg) {
  int val = fcntl(fd, cmd, arg);
  if (val == -1) {
    throw std::runtime_error("Fcntl error");
  }
  return val;
}

void Server::Setsockopt(int s, int level, int optname) {
  int optval = 1;
  if (setsockopt(s, level, optname, &optval, sizeof(optval)) < 0) {
    throw std::runtime_error("Setsockopt error");
  }
}

int Server::Bind(int sockfd, struct sockaddr *my_addr, int addrlen) {
  int val = bind(sockfd, my_addr, addrlen);
  if (val == -1) {
    Close(sockfd);
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

int Server::Select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                   struct timeval *timeout) {
  int val = select(n, readfds, writefds, exceptfds, timeout);
  if (val < 0) {
    throw std::runtime_error("Server close");
  }
  return val;
}

int Server::Accept(int s, struct sockaddr *addr, socklen_t *addrlen) {
  int val = accept(s, addr, addrlen);
  if (val < 0) {
    throw std::runtime_error("Accept error");
  }
  return val;
}