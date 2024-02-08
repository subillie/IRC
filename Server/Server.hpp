#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <ctime>
#include <map>
#include <queue>

#include "../Print/Print.hpp"

class Client;
class Channel;
class Messenger;

class Server {
 private:
  const int _port;
  const char *_password;
  int _serverFd;
  fd_set _readSet;   // 초기 상태의 set
  fd_set _readySet;  // event 발생으로 변한 set
  std::queue<std::string> _requests;

  void init();  // Server init : Select function
  void parse(std::string buffer);

  // Wrapper functions
  int Socket(int domain, int type, int protocol);
  int Fcntl(int fd, int cmd, int arg);
  void Setsockopt(int s, int level, int optname);
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
  static std::string _serverCreated;

  Server(int port, char *password);
  virtual ~Server();

  void run();  // Event loop
  void addClient(int fd);
  void deleteClient(int fd);
  static void sendToAllClients(Messenger msg);
};

#endif