#include "Messenger.hpp"

Messenger::Messenger() : _prefix(""), _param(""), _trailing("") {}

#include "../../Print/Print.hpp"  // for test

// Error functions

void Messenger::ErrNoSuchNick(int fd, const std::string& nick) {
  _prefix = SERVER;
  _param =
      ERR_NOSUCHNICK + " " + Server::_clientFds[fd]->getNickname() + " " + nick;
  _trailing = "No such nick/channel";
  printRed("ErrNoSuchNick");
  sendToClient(fd);
}

void Messenger::ErrNoSuchChannel(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_NOSUCHCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "No such channel";
  printRed("ErrNoSuchChannel");
  sendToClient(fd);
}
void Messenger::ErrCannotSendToChan(int fd) {
  printRed("ErrCannotSendToChan");
  sendToClient(fd);
}

void Messenger::ErrTooManyChannels(int fd) {
  _prefix = SERVER;
  _param = ERR_TOOMANYCHANNELS + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "You have joined too many channels";
  printRed("ErrTooManyChannels");
  sendToClient(fd);
}

void Messenger::ErrNoOrigin(int fd) {
  _prefix = SERVER;
  _param = ERR_NOORIGIN + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No origin specified";
  printRed("ErrNoOrigin");
  sendToClient(fd);
}

void Messenger::ErrUnknownCommand(int fd, const std::string& command) {
  _prefix = SERVER;
  _param = ERR_UNKNOWNCOMMAND + " " + Server::_clientFds[fd]->getNickname() +
           " " + command;
  _trailing = "Unknown command";
  printRed("UnknownCommand");
  sendToClient(fd);
}

void Messenger::ErrNoNickNameGiven(int fd) {
  _prefix = SERVER;
  _param = ERR_NONICKNAMEGIVEN + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No nickname given";
  printRed("ErrNoNickNameGiven");
  sendToClient(fd);
}

void Messenger::ErrErroneusNickName(int fd, const std::string& nick) {
  _prefix = SERVER;
  _param = ERR_ERRONEUSNICKNAME + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick;
  _trailing = "Erroneus nickname";
  printRed("ErrErroneusNickName");
  sendToClient(fd);
}

void Messenger::ErrNickNameInUse(int fd, const std::string& nick) {
  _prefix = SERVER;
  _param = ERR_NICKNAMEINUSE + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick;
  _trailing = "Nickname is already in use";
  printRed("ErrNickNameInUse");
  sendToClient(fd);
}

void Messenger::ErrNotRegistered(int fd) {
  _prefix = SERVER;
  _param = ERR_NOTREGISTERED + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "You have not registered";
  printRed("ErrNotRegistered");
  sendToClient(fd);
}

void Messenger::ErrNeedMoreParams(int fd, const std::string& command) {
  _prefix = SERVER;
  _param = ERR_NEEDMOREPARAMS + " " + Server::_clientFds[fd]->getNickname() +
           " " + command;
  _trailing = "Not enough parameters";
  printRed("NeedMoreParams");
  sendToClient(fd);
}

void Messenger::ErrAlreadyRegistered(int fd) {
  _prefix = SERVER;
  _param = ERR_ALREADYREGISTERED + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "You may not reregister";
  printRed("AlreadyRegistered");
  sendToClient(fd);
}

void Messenger::ErrPasswdMismatch(int fd) {
  _prefix = SERVER;
  _param = ERR_PASSWDMISMATCH + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "Password incorrect";
  printRed("ErrPasswdMismatch");
  sendToClient(fd);
}

void Messenger::ErrChannelIsFull(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_CHANNELISFULL + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "Cannot join channel (+l)";
  printRed("ErrChannelIsFull");
  sendToClient(fd);
}

void Messenger::ErrInviteOnlyChan(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_INVITEONLYCHAN + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "Cannot join channel (+i)";
  printRed("ErrInviteOnlyChan");
  sendToClient(fd);
}

void Messenger::ErrBadChannelKey(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_BADCHANNELKEY + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "Cannot join channel (+k)";
  printRed("ErrBadChannelKey");
  sendToClient(fd);
}

void Messenger::ErrBadChanMask(int fd) {
  _prefix = SERVER;
  _param = ERR_BADCHANMASK + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "Bad Channel Mask";
  printRed("ErrBadChanMask");
  sendToClient(fd);
}

void Messenger::ErrNoRecipient(int fd) {
  printRed("ErrNoRecipient");
  sendToClient(fd);
}
void Messenger::ErrNoTextToSend(int fd) {
  printRed("ErrNoTextToSend");
  sendToClient(fd);
}

void Messenger::ErrUnknownCommand(int fd) {
  _prefix = SERVER;
  _param = ERR_UMODEUNKNOWNFLAG + " " + client->getNickname();
  _trailing = "Unknown MODE flag";
  printRed("ErrUModeUnknownFlag");
  sendToClient(fd);
}
void Messenger::ErrNoTextToSend(int fd) {
  printRed("ErrNoTextToSend");
  sendToClient(fd);
}

void Messenger::ErrUModeUnknownFlag(int fd) {
  Client* client = Server::_clientFds[fd];

  _prefix = SERVER;
  _param = ERR_UMODEUNKNOWNFLAG + " " + client->getNickname();
  _trailing = "Unknown MODE flag";
  printRed("ErrUModeUnknownFlag");
  sendToClient(fd);
}

void Messenger::ErrUsersDontMatch(int fd) {
  Client* client = Server::_clientFds[fd];

  _prefix = SERVER;
  _param = ERR_USERSDONTMATCH + " " + client->getNickname();
  _trailing = "Cant change mode for other users";
  printRed("ErrUsersDontMatch");
  sendToClient(fd);
}

void Messenger::ErrUnexpected(int fd) {  // TODO: implement
  _prefix = SERVER;
  printRed("Unexpected");
  sendToClient(fd);
}

// Reply functions
void Messenger::RplWelcome(int fd) {
  const std::string& nick = Server::_clientFds[fd]->getNickname();
  const std::string squirtle =
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡶⠞⠛⠛⠉⠉⠛⠛⠳⢦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⣠⡾⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⣼⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣄⠀⢹⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⣼⠃⠀⠀⣠⡖⢠⠀⠀⠀⠀⠀⠀⠀⠀⣧⣼⣷⠀⢿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⡟⠀⠀⢠⢿⣷⣶⡇⠀⠀⠀⠀⠀⠀⠀⡿⣿⡿⠀⠘⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⣇⠀⠀⢸⠸⠻⡿⠇⠀⠀⠀⠀⠀⠀⠀⠐⠒⠈⢀⠀⢹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⢀⣄⡀⣿⠀⠀⠀⠁⠀⠉⠁⢀⣀⣀⣀⣄⣤⠴⢶⣶⣿⡏⠀⣸⣃⣀⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⣠⣾⠉⠛⠛⠦⠤⣄⡀⢿⡋⠉⠉⠁⠀⠀⠉⠁⠀⠀⢈⡟⢀⡼⠛⠉⠉⠉⠉⠉⠛⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⣿⠀⠀⠀⠀⠀⠀⠀⠉⠛⢷⣦⣀⠀⣀⣠⠤⠖⠒⠒⢛⣛⣻⣷⡖⣀⡀⠀⠀⠀⠀⠀⢹⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⣿⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⡋⢉⣠⠴⠖⠚⠉⠉⠁⠉⠻⣍⣹⣶⣦⣀⡀⠀⠀⣸⣷⠶⠶⠶⠶⢦⣤⣴⣦⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠈⠙⠳⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣉⣀⠀⠀⠀⠀⣀⣠⠤⠖⠛⠙⢿⣄⠈⠉⠙⠻⢿⣇⠀⠀⠀⠀⢠⠟⠀⠘⠛⠻⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠈⠛⢦⣄⡀⠀⠀⠀⠀⣠⣏⡉⠉⠉⠉⢉⡿⠟⠒⠒⠤⣄⡀⠀⠉⢦⡀⠀⠀⠀⠉⢧⠀⠀⠀⠋⠀⠀⠀⠀⠀⠉⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠉⠛⢷⣶⣿⣿⣭⣭⡉⠑⢦⣴⠃⠀⠀⠀⠀⠀⠀⣙⣦⣠⣄⡹⢦⣀⠀⠀⠈⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣁⣀⣠⣤⣄⣀⡀⠀⠀⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣆⠘⡇⠀⠀⠀⠀⣶⠶⠞⠉⠛⠋⠘⣇⠀⠈⠳⢦⡀⠘⡆⠀⠀⠀⠀⠀⠀⠀⣰⠟⠋⠁⠀⠀⠀⠉⠙⠳⣤⡀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⡄⣧⠀⠀⠀⠀⣇⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠙⠳⡿⣶⣶⣤⣀⣀⣠⡴⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⡄⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣷⡘⢧⡀⠀⠀⢿⠀⠀⠀⠀⠀⠀⣼⠀⢀⣠⣤⣄⡼⠁⣼⠀⠀⠉⠉⣽⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡄\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣷⣤⡉⠓⠦⠼⣧⡀⠀⠀⠀⣰⡇⢠⠋⠀⠀⠀⠙⠶⣯⣀⠀⠀⠀⣿⠀⠀⠀⠀⡴⠚⠛⠳⣆⠀⠀⠀⠀⠸⣇\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣶⣶⣦⣽⣶⣶⣾⣉⣉⠙⣄⠀⠀⠀⠀⠀⠈⠙⠛⠛⠛⠻⡆⠀⠀⠀⠀⠀⠀⠀⢹⡆⠀⠀⠀⠀⣿\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣄⠀⠀⠀⠀⠀⢀⡾⠀⠀⠀⠀⢰⡇\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠛⠿⠿⠿⠿⠛⠛⠉⠁⠀⠀⠀⠙⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠉⠳⠶⢤⡤⠴⠛⠁⠀⠀⠀⢠⡿⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⢶⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠟⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⠶⣦⣤⣤⣀⣀⣀⣀⣠⣤⡴⠾⠋⠁⠀⠀⠀\n"
      "\033[0;34m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀\n";

  const std::string& hello =
      "\033[0;36m _  _ ___ _    _    ___  _ \n"
      "\033[0;36m| || | __| |  | |  / _ \\| |\n"
      "\033[0;36m| __ | _|| |__| |_| (_) |_|\n"
      "\033[0;36m|_||_|___|____|____\\___/(_) \033[0m";

  _prefix = SERVER;
  _param = RPL_WELCOME + " " + nick;
  _trailing = squirtle + hello + nick;
  printRed("RplWelcome");
  sendToClient(fd);
}

void Messenger::RplYourHost(int fd) {
  _prefix = SERVER;
  _param = RPL_YOURHOST + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "Your host is " + SERVER + ", running version " + VERSION;
  printRed("RplYourHost");
  sendToClient(fd);
}
void Messenger::RplCreated(int fd) {
  _prefix = SERVER;
  _param = RPL_CREATED + " " + Server::_clientFds[fd]->getNickname();
  // TODO: time server was created
  // _trailing = "This server was created " + datetime;
  printRed("RplCreated");
  sendToClient(fd);
}

void Messenger::RplMyinfo(int fd) {
  _prefix = SERVER;
  _param = RPL_MYINFO + " " + Server::_clientFds[fd]->getNickname() + " " +
           SERVER + " " + VERSION + " " + AVAILABLE_USER_MODES + " " +
           AVAILABLE_CHAN_MODES;
  printRed("RplMyinfo");
  sendToClient(fd);
}

void Messenger::RplUModeIs(int fd, const std::string& usermode) {
  _prefix = SERVER;
  _param = RPL_UMODEIS + " " + Server::_clientFds[fd]->getNickname() + " " +
           usermode;
  printRed("RplUModeIs");
  sendToClient(fd);
}

void Messenger::RplTopic(int fd, const std::string& channel,
                         const std::string& topic) {
  _prefix = SERVER;
  _param =
      RPL_TOPIC + " " + Server::_clientFds[fd]->getNickname() + " " + channel;
  _trailing = topic;
  printRed("RplTopic");
  sendToClient(fd);
}

void Messenger::RplInviteList(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_INVITELIST + " " + Server::_clientFds[fd]->getNickname() + " " +
           channel;
  printRed("RplInviteList");
  sendToClient(fd);
}

void Messenger::RplNamReply(int fd, const std::string& channel,
                            const std::string& nick) {
  _prefix = SERVER;
  _param = RPL_NAMREPLY + " " + Server::_clientFds[fd]->getNickname() + " = " +
           channel;
  _trailing = nick;
  printRed("RplNamReply");
  sendToClient(fd);
}

void Messenger::RplEndOfNames(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_ENDOFNAMES + " " + Server::_clientFds[fd]->getNickname() + " " +
           channel;
  _trailing = "End of /NAMES list";
  printRed("RplEndOfNames");
  sendToClient(fd);
}

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
  _prefix.clear();
  _param.clear();
  _trailing.clear();
}
