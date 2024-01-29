#include "Messenger.hpp"

Messenger::Messenger() : _prefix(""), _param(""), _trailing("") {}

#include "../../Print/Print.hpp"  // for test

// Error functions
void Messenger::ErrNoSuchChannel(int fd) {
  printRed("NoSuchChannel");
  sendToClient(fd);
}

void Messenger::ErrNeedMoreParams(int fd, const std::string& command) {
  Client* client = Server::_clientFds[fd];

  _prefix = SERVER;
  _param = ERR_NEEDMOREPARAMS + " " + client->getNickname() + command;
  _trailing = "Not enough parameters";
  printRed("NeedMoreParams");
  sendToClient(fd);
}

void Messenger::ErrAlreadyRegistered(int fd) {
  Client* client = Server::_clientFds[fd];
  _prefix = SERVER;
  _param = ERR_ALREADYREGISTERED + " " + client->getNickname();
  _trailing = "You may not reregister";
  printRed("AlreadyRegistered");
  sendToClient(fd);
}

void Messenger::ErrPasswdMismatch(int fd) {
  Client* client = Server::_clientFds[fd];
  _prefix = SERVER;
  _param = ERR_PASSWDMISMATCH + " " + client->getNickname();
  _trailing = "Password incorrect";
  printRed("ErrPasswdMismatch");
  sendToClient(fd);
}

void Messenger::ErrNoNickNameGiven(int fd) {
  _prefix = SERVER;
  printRed("ErrNoNickNameGiven");
  sendToClient(fd);
}

void Messenger::ErrErroneusNickName(int fd) {
  _prefix = SERVER;
  printRed("ErrErroneusNickName");
  sendToClient(fd);
}

void Messenger::ErrNickNameInUse(int fd) {
  _prefix = SERVER;
  printRed("ErrNickNameInUse");
  sendToClient(fd);
}

void Messenger::ErrNoOrigin(int fd) {
  _prefix = SERVER;
  printRed("ErrNoOrigin");
  sendToClient(fd);
}

void Messenger::ErrUnknownCommand(int fd) {
  _prefix = SERVER;
  printRed("UnknownCommand");
  sendToClient(fd);
}

void Messenger::ErrPasswdMismatch(int fd) {
  printRed("ErrPasswdMismatch");
  sendToClient(fd);
}

void Messenger::ErrUnexpected(int fd) {
  _prefix = SERVER;
  printRed("Unexpected");
  sendToClient(fd);
}

// Reply functions
void Messenger::RplWelcome(int fd) {
  Client* client = Server::_clientFds[fd];
  const std::string& nick = client->getNickname();
  // const std::string& username = client->getUsername();
  // const std::string& hostname = client->getHostname();
  const std::string squirtle =
      "\033[0;34m⠀⠀⠀⠀⠀⣀⠤⠤⠤⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⡰⠋⠀⠀⠀⠀⠀⠀⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⢠⠁⢰⣴⠀⠀⠀⠀⣿⡇⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⢀⣸⠀⠈⠙⠃⣀⣀⡀⣤⡄⢸⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⢰⠃⠉⠁⠂⢦⣀⢀⡀⠤⠤⣥⣌⡀⠀⠈⠱⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠘⠦⡀⠀⠀⠀⠈⡄⠂⠉⠀⣀⠵⢵⡒⠠⢴⡋⠉⢑⠖⠦⢄⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠈⠲⢤⣤⣴⡥⢄⡨⠋⠀⠒⢄⡑⣄⠀⠈⠄⠀⠀⠀⠈⡝⢀⣀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠈⢿⣿⣿⣆⡇⠀⠀⠊⠉⠉⡆⠈⠢⣶⣀⡀⢀⡰⠋⠀⠀⠉⠑⡄⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⢿⣿⣿⣔⠀⠠⡀⠀⢀⡇⠀⠀⠠⣇⠈⢹⠀⠀⡀⠀⠀⠀⠘⡄\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠙⠛⢿⣿⣿⣿⣿⣶⣶⢆⠀⠀⠈⠉⠈⢄⠀⠀⠀⠂⠀⢀⠇\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠁⠀⠀⠑⠦⣄⠀⠀⠀⠁⠀⠈⠀⢀⠎⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠒⠲⠖⠒⠊⠁⠀⠀\n";
  const std::string& hello =
      "\033[0;36m _  _ ___ _    _    ___  _ \n"
      "\033[0;36m| || | __| |  | |  / _ \\| |\n"
      "\033[0;36m| __ | _|| |__| |_| (_) |_|\n"
      "\033[0;36m|_||_|___|____|____\\___/(_) \033[0m";

  _prefix = SERVER;
  _param = RPL_WELCOME + " " + nick;
  _trailing =
      squirtle + hello + nick;  //+ "!" + username + "@" + hostname (optional)

  printRed("RplWelcome");
  sendToClient(fd);
}

void Messenger::RplYourHost(int fd) {
  _prefix = SERVER;
  printRed("RplYourHost");
  sendToClient(fd);
}  // 002

void Messenger::RplCreated(int fd) {
  _prefix = SERVER;
  printRed("RplCreated");
  sendToClient(fd);
}  // 003

void Messenger::RplMyinfo(int fd) {
  _prefix = SERVER;
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
