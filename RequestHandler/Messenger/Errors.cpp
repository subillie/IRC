#include "Messenger.hpp"

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

void Messenger::ErrCannotSendToChan(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_CANNOTSENDTOCHAN + " " + Server::_clientFds[fd]->getNickname() +
           channel;
  _trailing = "Cannot send to channel";
  printRed("ErrCannotSendToChan");
  sendToClient(fd);
}

void Messenger::ErrTooManyChannels(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_TOOMANYCHANNELS + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
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

void Messenger::ErrNoRecipient(int fd) {
  _prefix = SERVER;
  _param = ERR_NORECIPIENT + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No recipient given";
  printRed("ErrNoRecipient");
  sendToClient(fd);
}

void Messenger::ErrNoTextToSend(int fd) {
  _prefix = SERVER;
  _param = ERR_NOTEXTTOSEND + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No text to send";
  printRed("ErrNoTextToSend");
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

void Messenger::ErrUserNotInChannel(int fd, const std::string& nick,
                                    const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_USERNOTINCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick + " " + channel;
  _trailing = "They aren't on that channel";
  printRed("ErrUserNotInChannel");
  sendToClient(fd);
}

void Messenger::ErrNotOnChannel(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_NOTONCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "You're not on that channel";
  printRed("ErrNotOnChannel");
  sendToClient(fd);
}

void Messenger::ErrUserOnChannel(int fd, const std::string& nick,
                                 const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_USERONCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick + " " + channel;
  _trailing = "is already on channel";
  printRed("ErrUserOnChannel");
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

void Messenger::ErrUnknownMode(int fd, const std::string& mode) {
  _prefix = SERVER;
  _param = ERR_UNKNOWNMODE + " " + mode;
  _trailing = "is unknown mode char to our server";
  printRed("ErrUnknownMode");
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

void Messenger::ErrChanOPrivsNeeded(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_CHANOPRIVSNEEDED + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "You're not channel operator";
  printRed("ErrChanOPrivsNeeded");
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

void Messenger::ErrInvalidModeParam(int fd, const std::string& channel,
                                    const char& mode) {
  _prefix = SERVER;
  _param = ERR_INVALIDMODEPARAM + " " + channel + " " + mode + " *";
  // _trailing = "You must specify a parameter for this mode";
  printRed("ErrInvalidModeParam");
  sendToClient(fd);
}

// Unexpected result
void Messenger::ErrUnexpected(int fd) {
  _prefix = SERVER;
  printRed("Unexpected");
  sendToClient(fd);
}