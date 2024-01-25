#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <map>

#include "../Print/Print.hpp"
#define FD_MAX 1024

class Client;
class Channel;

class Server {
 private:
  int _port;
  char *_password;
  int _serverFd;
  fd_set _readSet;   // 초기 상태의 set
  fd_set _readySet;  // event 발생으로 변한 set

  void init();  // Server init : Select function

  // Wrapper functions
  int Socket(int domain, int type, int protocol);
  int Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
  void Close(int fd);
  void Listen(int sockfd, int backlog);
  int Select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
             struct timeval *timeout);
  int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
  int Recv(int fd, char *buffer, int bufLen, int n);

 public:
  static std::map<int, Client *> _clientFds;
  static std::map<std::string, Client *> _clientNicks;
  static std::map<std::string, Channel *> _channelNames;

  Server(int port, char *password);

  void run();  // event loop
  void addClient(int fd);
  void deleteClient(int fd);
};

#endif