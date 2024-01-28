#include "Messenger.hpp"

Messenger::Messenger() : _prefix(""), _param(""), _trailing("") {}

#include "../../Print/Print.hpp"  // for test

// Error function
void Messenger::ErrNeedMoreParams(int fd) {
  printRed("NeedMoreParams");
  sendToClient(fd);
}

void Messenger::ErrAlreadyRegistered(int fd) {
  printRed("AlreadyRegistered");
  sendToClient(fd);
}

void Messenger::ErrPasswdMismatch(int fd) {
  printRed("ErrPasswdMismatch");
  sendToClient(fd);
}

void Messenger::ErrNoNickNameGiven(int fd) {
  printRed("ErrNoNickNameGiven");
  sendToClient(fd);
}

void Messenger::ErrErroneusNickName(int fd) {
  printRed("ErrErroneusNickName");
  sendToClient(fd);
}

void Messenger::ErrNickNameInUse(int fd) {
  printRed("ErrNickNameInUse");
  sendToClient(fd);
}

void Messenger::ErrNoOrigin(int fd) {
  printRed("ErrNoOrigin");
  sendToClient(fd);
}

void Messenger::ErrUnknownCommand(int fd) {
  printRed("UnknownCommand");
  sendToClient(fd);
}

void Messenger::ErrUnexpected(int fd) {
  printRed("Unexpected");
  sendToClient(fd);
}

// Reply function
void Messenger::RplWelcome(int fd) {
  Client* client = Server::_clientFds[fd];
  const std::string& nick = client->getNickname();
  const std::string& username = client->getUsername();
  const std::string& hostname = client->getHostname();

  _prefix = SERVER;
  _param = RPL_WELCOME + " " + nick;
  _trailing = "Welcome to private irc server! " + nick + "!" + username + "@" +
              hostname;
  printRed("RplWelcome");
  sendToClient(fd);
}

void Messenger::RplYourHost(int fd) {
  printRed("RplYourHost");
  sendToClient(fd);
}  // 002

void Messenger::RplCreated(int fd) {
  printRed("RplCreated");
  sendToClient(fd);
}  // 003

void Messenger::RplMyinfo(int fd) {
  printRed("RplMyinfo");
  sendToClient(fd);
}  // 004

void Messenger::setPrefix(const std::string& prefix) { _prefix = prefix; }

void Messenger::setParam(const std::string& param) { _param = param; }

void Messenger::setTrailing(const std::string& trailing) {
  _trailing = trailing;
}

void Messenger::sendToClient(int fd) {
  if (!_prefix.empty()) _prefix = ":" + _prefix + " ";
  if (!_trailing.empty()) _trailing = " :" + _trailing;
  std::string response = _prefix + _param + _trailing + CRLF;
  printCyan(response);
  if (send(fd, response.c_str(), response.length(), 0) == -1) {
    throw std::runtime_error("Send error");
  }
}
