#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <set>
#include <string>

#include "../Channel/Channel.hpp"

#define MAX_CHANNEL 10

class Client {
 private:
  int _fd;
  bool _isRegistered;
  bool _isQuit;
  std::string _mode;
  std::string _username;
  std::string _nickname;
  std::string _password;
  std::string _hostname;
  std::string _realname;
  std::set<std::string> _channels;
  std::queue<std::string> _replies;

 public:
  std::string buffer;

  Client(int fd);

  bool isMaxJoined() const;
  void addChannel(const std::string &channel);
  void leaveChannel(Channel *channel);

  void setIsRegistered(bool val);
  void setIsQuit(bool val);
  void setMode(const std::string &mode);
  void setUsername(const std::string &username);
  void setNickname(const std::string &nickname);
  void setPassword(const std::string &password);
  void setHostname(const std::string &hostname);
  void setRealname(const std::string &realname);
  const int &getFd() const;
  bool getIsRegistered() const;
  bool getIsQuit() const;
  const std::string &getMode() const;
  const std::string &getUsername() const;
  const std::string &getNickname() const;
  const std::string &getPassword() const;
  const std::string &getHostname() const;
  const std::string &getRealname() const;
  const std::string getPrefix() const;
  const std::set<std::string> &getChannels() const;

  void sendReplies();
  void addReplies(const std::string &replies);
};

std::ostream &operator<<(std::ostream &os, const Client &client);

#endif
