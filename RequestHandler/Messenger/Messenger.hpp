#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <string>
#include <vector>

#include "../../Macros/Characters.hpp"

class Messenger {
 private:
  std::string _prefix;
  std::string _command;
  std::string _trailing;

 public:
  Messenger();
  void setPrefix(const std::string& prefix);
  void setCommand(const std::string& command);  // token[1] + token[2] ....
  void setTrailing(const std::string& trailing);
  void sendToClient(int fd);
};

#endif