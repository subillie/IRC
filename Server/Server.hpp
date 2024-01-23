#ifndef SERVER_HPP
#define SERVER_HPP

#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <map>

#define FD_MAX 1024

class Client;
class Channel;

class Server {
 private:
  char *_port;
  char *_password;
  int _serverFd;
  fd_set _readSet;   // 초기 상태의 set
  fd_set _readySet;  // event 발생으로 변한 set
  static std::map<int, Client *> _clientFds;
  static std::map<std::string, Client *> _clientNicks;
  static std::map<std::string, Channel *> _channelNames;

  void init();  // Server init : Select function

  // Wrapper functions
  void Getaddrinfo(const char *node, const char *service,
                   const struct addrinfo *hints, struct addrinfo **res);
  int Socket(int domain, int type, int protocol);
  int Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
  void Setsockopt(int s, int level, int optname, const void *optval,
                  int optlen);
  void Close(int fd);
  void Listen(int sockfd, int backlog);

 public:
  Server(char *port, char *password);
  void run();  // event loop
};

#endif