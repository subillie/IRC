#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
 private:
  int _fd;
  std::string _username;
  std::string _nickname;
  std::string _password;
  bool _isAuthenticated;

 public:
  Client(int fd);
  void setUsername();
  void setNickname();
  void setPassword();
  const int &getFd() const;
  const std::string &getUsername() const;
  const std::string &getNickname() const;
  const std::string &getPassword() const;
  bool getIsAuthenticated() const;
};

#endif
