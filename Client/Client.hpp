#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
 private:
  int _fd;
  std::string _username;
  std::string _nickname;
  std::string _password;

 public:
  Client(int fd);
};

#endif
