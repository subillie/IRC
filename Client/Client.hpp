#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>

class Client {
 private:
  int _fd;
  std::string _mode;
  std::string _username;
  std::string _nickname;
  std::string _password;
  std::string _hostname;
  bool _isRegistered;

 public:
  Client(int fd);
  void setMode(const std::string &mode);
  void setUsername(const std::string &username);
  void setNickname(const std::string &nickname);
  void setPassword(const std::string &password);
  void setHostname(const std::string &hostname);
  const int &getFd() const;
  const std::string &getMode() const;
  const std::string &getUsername() const;
  const std::string &getNickname() const;
  const std::string &getPassword() const;
  const std::string &getHostname() const;
  bool getIsRegistered() const;
  void setIsRegisterd(bool val);
};

std::ostream &operator<<(std::ostream &os, const Client &client);

#endif
