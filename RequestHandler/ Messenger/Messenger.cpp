#include "Messenger.hpp"

Messenger::Messenger() {}

void Messenger::setPrefix(const std::string& prefix) { _prefix = prefix; }

void Messenger::setCommand(const std::string& command) { _command = command; }

void Messenger::sendToClient(int fd, const std::string& msg) {
  const std::string reply = msg + CRLF;
  if (send(fd, &reply, reply.length(), 0) == -1) {
    throw std::runtime_error("Send error");
  }
}