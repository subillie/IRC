#include "Server.hpp"
#include "../Client/Client.hpp"

Server::Server(char *port, char *password) : _port(port), _password(password) {}

void Server::init()
{
  // 가능한 서버 주소 리스트 받아오기
  struct addrinfo sockOpt, *sockAddrList, *iter;
  memset(&sockOpt, 0, sizeof(struct addrinfo));
  sockOpt.ai_socktype = SOCK_STREAM;             // Accept TCP connections
  sockOpt.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // 시스템에서 사용 가능한 IP만
  sockOpt.ai_flags |= AI_NUMERICSERV;            // port 번호를 숫자로 지정하도록
  Getaddrinfo(NULL, _port, &sockOpt, &sockAddrList);

  // 그 리스트에서 우리가 bind할 하나를 찾음
  for (iter = sockAddrList; iter; iter->ai_next)
  {
    // socket descriptor 생성
    _serverFd = Socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
    if (_serverFd < 0)
    {
      continue;
    }

    // SO_REUSEADDR - 이전에 사용된 주소와 포트를 빠르게 재사용할 수 있도록 함
    // bind에서 발생할 수 있는 "Address already in use" error 제거
    int optval = 1;
    Setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
               sizeof(int));

    // 만든 socket descriptor를 address에 bind
    if (Bind(_serverFd, iter->ai_addr, iter->ai_addrlen) == 0)
    {
      break; // Success
    }
    Close(_serverFd); // Fail
    FD_ZERO(&_readSet);
    FD_SET(_serverFd, &_readSet);
  }

  freeaddrinfo(sockAddrList);
  if (!iter)
  {
    throw std::runtime_error("No address found");
  }
  listen(_serverFd, FD_MAX);
}

void Server::run()
{
  int tmp;
  int fdCount = _serverFd;
  init();
  while (true)
  {
    _readySet = _readSet;
    // TODO: timeout
    // TODO: select wrapper
    if (tmp = select(fdCount + 1, &_readySet, 0, 0, 0) == -1)
    {
      throw std::runtime_error("select error");
    }
    for (int i = 0; i <= fdCount; i++)
    {
      if (FD_ISSET(i, &_readySet))
      {
        // accept
        if (i == _serverFd)
        {
          sockaddr_in client_addr;
          socklen_t client_addr_len = sizeof(client_addr);
          int clientFd = accept(_serverFd, reinterpret_cast<struct sockaddr *>(&client_addr), &client_addr_len);
          if (clientFd == -1)
            throw std::runtime_error("accept failed");
          _clientFds[clientFd] = new Client(clientFd);
          FD_SET(clientFd, &_readSet);
        }
        else
        {
          // request handler
        }
        //
        // getnameinfo
      }
    }
    // 명령어 실행
  }
}

void Getaddrinfo(const char *node, const char *service,
                 const struct addrinfo *hints, struct addrinfo **res)
{
  if (getaddrinfo(node, service, hints, res) != 0)
  {
    throw std::runtime_error("Getaddrinfo error");
  }
}

int Server::Socket(int domain, int type, int protocol)
{
  int val;
  if (val = socket(domain, type, protocol))
  {
    throw std::runtime_error("Socket error");
  }
  return val;
}

void Server::Setsockopt(int s, int level, int optname, const void *optval,
                        int optlen)
{
  if (setsockopt(s, level, optname, optval, optlen) < 0)
  {
    throw std::runtime_error("Setsockopt error");
  }
}

int Server::Bind(int sockfd, struct sockaddr *my_addr, int addrlen)
{
  int val;
  if (val = bind(sockfd, my_addr, addrlen) < 0)
  {
    throw std::runtime_error("Bind error");
  }
  return val;
}

void Server::Close(int fd)
{
  if (close(fd) < 0)
  {
    throw std::runtime_error("Close error");
  }
}

void Server::Listen(int sockfd, int backlog)
{
  if (listen(sockfd, backlog) < 0)
  {
    Close(sockfd);
    throw std::runtime_error("Listen error");
  }
}