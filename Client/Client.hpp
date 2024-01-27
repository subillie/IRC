#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
 private:
  int _fd;
  std::string _username;
  std::string _nickname;
  std::string _password;
  bool _isRegistered;

 public:
  Client(int fd);
  void setUsername(const std::string &username);
  void setNickname(const std::string &nickname);
  void setPassword(const std::string &password);
  const int &getFd() const;
  const std::string &getUsername() const;
  const std::string &getNickname() const;
  const std::string &getPassword() const;
  bool getIsRegistered() const;
  void setIsRegisterd(bool val);
};

#endif
