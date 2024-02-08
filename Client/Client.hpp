#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <set>
#include <string>

#define MAX_CHANNEL 10

class Client {
 private:
  int _fd;
  std::string _mode;
  std::string _username;
  std::string _nickname;
  std::string _password;
  std::string _hostname;
  std::string _realname;
  std::set<std::string> _channels;
  bool _isRegistered;

 public:
  std::string buffer;

  Client(int fd);

  void addChannel(const std::string &channel);
  void removeChannel(const std::string &channel);
  bool isMaxJoined() const;

  void setMode(const std::string &mode);
  void setUsername(const std::string &username);
  void setNickname(const std::string &nickname);
  void setPassword(const std::string &password);
  void setHostname(const std::string &hostname);
  void setRealname(const std::string &realname);
  void setIsRegisterd(bool val);
  const int &getFd() const;
  const std::string &getMode() const;
  const std::string &getUsername() const;
  const std::string &getNickname() const;
  const std::string &getPassword() const;
  const std::string &getHostname() const;
  const std::string &getRealname() const;
  const std::string getPrefix() const;
  const std::set<std::string> &getChannels() const;
  bool getIsRegistered() const;
};

std::ostream &operator<<(std::ostream &os, const Client &client);

#endif
