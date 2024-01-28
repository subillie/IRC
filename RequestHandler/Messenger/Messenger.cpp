#include "Messenger.hpp"

Messenger::Messenger() : _prefix(""), _param(""), _trailing("") {}

#include "../../Print/Print.hpp"

// Error functions
void Messenger::ErrNoSuchChannel(int fd) {
  printRed("NoSuchChannel");
  sendToClient(fd);
}  // 403

void Messenger::ErrNoOrigin(int fd) {
  printRed("ErrNoOrigin");
  sendToClient(fd);
}  // 409

void Messenger::ErrUnknownCommand(int fd) {
  printRed("UnknownCommand");
  sendToClient(fd);
}  // 421

void Messenger::ErrNoNickNameGiven(int fd) {
  printRed("ErrNoNickNameGiven");
  sendToClient(fd);
}  // 431

void Messenger::ErrErroneusNickName(int fd) {
  printRed("ErrErroneusNickName");
  sendToClient(fd);
}  // 432

void Messenger::ErrNickNameInUse(int fd) {
  printRed("ErrNickNameInUse");
  sendToClient(fd);
}  // 433

void Messenger::ErrNeedMoreParams(int fd) {
  printRed("NeedMoreParams");
  sendToClient(fd);
}  // 461

void Messenger::ErrAlreadyRegistered(int fd) {
  printRed("AlreadyRegistered");
  sendToClient(fd);
}  // 462

void Messenger::ErrPasswdMismatch(int fd) {
  printRed("ErrPasswdMismatch");
  sendToClient(fd);
}  // 464

void Messenger::ErrUnexpected(int fd) {
  printRed("Unexpected");
  sendToClient(fd);
}

// Reply functions
void Messenger::RplWelcome(int fd) {
  Client* client = Server::_clientFds[fd];
  setPrefix(":" + SERVER);
  const std::string& nick = client->getNickname();
  const std::string& username = client->getUsername();
  const std::string& hostname = client->getHostname();
  setParam(RPL_WELCOME + " " + nick);
  setTrailing(":Welcome to private irc server! " + nick + "!" + username + "@" +
              hostname);
  printRed("RplWelcome");
  sendToClient(fd);
}  // 001

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
  std::string response = _prefix + " " + _param + " " + _trailing + CRLF;
  printCyan(response);
  if (send(fd, response.c_str(), response.length(), 0) == -1) {
    throw std::runtime_error("Send error");
  }
}
