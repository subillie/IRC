#include "Messenger.hpp"

void Messenger::ErrNoSuchNick(int fd, const std::string& nick) {
  _prefix = SERVER;
  _param =
      ERR_NOSUCHNICK + " " + Server::_clientFds[fd]->getNickname() + " " + nick;
  _trailing = "No such nick";
  printRed("ErrNoSuchNick");
  addRespondToClient(fd);
}

void Messenger::ErrNoSuchChannel(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_NOSUCHCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "No such channel";
  printRed("ErrNoSuchChannel");
  addRespondToClient(fd);
}

void Messenger::ErrCannotSendToChan(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_CANNOTSENDTOCHAN + " " + Server::_clientFds[fd]->getNickname() +
           channel;
  _trailing = "Cannot send to channel";
  printRed("ErrCannotSendToChan");
  addRespondToClient(fd);
}

void Messenger::ErrTooManyChannels(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_TOOMANYCHANNELS + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "You have joined too many channels";
  printRed("ErrTooManyChannels");
  addRespondToClient(fd);
}

void Messenger::ErrNoOrigin(int fd) {
  _prefix = SERVER;
  _param = ERR_NOORIGIN + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No origin specified";
  printRed("ErrNoOrigin");
  addRespondToClient(fd);
}

void Messenger::ErrNoRecipient(int fd) {
  _prefix = SERVER;
  _param = ERR_NORECIPIENT + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No recipient given";
  printRed("ErrNoRecipient");
  addRespondToClient(fd);
}

void Messenger::ErrNoTextToSend(int fd) {
  _prefix = SERVER;
  _param = ERR_NOTEXTTOSEND + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No text to send";
  printRed("ErrNoTextToSend");
  addRespondToClient(fd);
}

void Messenger::ErrUnknownCommand(int fd, const std::string& command) {
  _prefix = SERVER;
  _param = ERR_UNKNOWNCOMMAND + " " + Server::_clientFds[fd]->getNickname() +
           " " + command;
  _trailing = "Unknown command";
  printRed("UnknownCommand");
  addRespondToClient(fd);
}

void Messenger::ErrNoNickNameGiven(int fd) {
  _prefix = SERVER;
  _param = ERR_NONICKNAMEGIVEN + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "No nickname given";
  printRed("ErrNoNickNameGiven");
  addRespondToClient(fd);
}

void Messenger::ErrErroneusNickName(int fd, const std::string& nick) {
  _prefix = SERVER;
  _param = ERR_ERRONEUSNICKNAME + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick;
  _trailing = "Erroneus nickname";
  printRed("ErrErroneusNickName");
  addRespondToClient(fd);
}

void Messenger::ErrNickNameInUse(int fd, const std::string& nick) {
  _prefix = SERVER;
  _param = ERR_NICKNAMEINUSE + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick;
  _trailing = "Nickname is already in use";
  printRed("ErrNickNameInUse");
  addRespondToClient(fd);
}

void Messenger::ErrUserNotInChannel(int fd, const std::string& nick,
                                    const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_USERNOTINCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick + " " + channel;
  _trailing = "They aren't on that channel";
  printRed("ErrUserNotInChannel");
  addRespondToClient(fd);
}

void Messenger::ErrNotOnChannel(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_NOTONCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "You're not on that channel";
  printRed("ErrNotOnChannel");
  addRespondToClient(fd);
}

void Messenger::ErrUserOnChannel(int fd, const std::string& nick,
                                 const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_USERONCHANNEL + " " + Server::_clientFds[fd]->getNickname() +
           " " + nick + " " + channel;
  _trailing = "is already on channel";
  printRed("ErrUserOnChannel");
  addRespondToClient(fd);
}

void Messenger::ErrNotRegistered(int fd) {
  _prefix = SERVER;
  _param = ERR_NOTREGISTERED + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "You have not registered";
  printRed("ErrNotRegistered");
  addRespondToClient(fd);
}

void Messenger::ErrNeedMoreParams(int fd, const std::string& command) {
  _prefix = SERVER;
  _param = ERR_NEEDMOREPARAMS + " " + Server::_clientFds[fd]->getNickname() +
           " " + command;
  _trailing = "Not enough parameters";
  printRed("NeedMoreParams");
  addRespondToClient(fd);
}

void Messenger::ErrAlreadyRegistered(int fd) {
  _prefix = SERVER;
  _param = ERR_ALREADYREGISTERED + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "You may not reregister";
  printRed("AlreadyRegistered");
  addRespondToClient(fd);
}

void Messenger::ErrPasswdMismatch(int fd) {
  _prefix = SERVER;
  _param = ERR_PASSWDMISMATCH + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "Password incorrect";
  printRed("ErrPasswdMismatch");
  addRespondToClient(fd);
}

void Messenger::ErrKeySet(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_KEYSET + " " + Server::_clientFds[fd]->getNickname() + channel;
  _trailing = "Channel key already set";
  printRed("ErrKeySet");
  addRespondToClient(fd);
}

void Messenger::ErrChannelIsFull(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_CHANNELISFULL + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "Cannot join channel (+l)";
  printRed("ErrChannelIsFull");
  addRespondToClient(fd);
}

void Messenger::ErrUnknownMode(int fd, const std::string& mode) {
  _prefix = SERVER;
  _param = ERR_UNKNOWNMODE + " " + mode;
  _trailing = "is unknown mode char to our server";
  printRed("ErrUnknownMode");
  addRespondToClient(fd);
}

void Messenger::ErrInviteOnlyChan(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_INVITEONLYCHAN + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "Cannot join channel (+i)";
  printRed("ErrInviteOnlyChan");
  addRespondToClient(fd);
}

void Messenger::ErrBadChannelKey(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_BADCHANNELKEY + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "Cannot join channel (+k)";
  printRed("ErrBadChannelKey");
  addRespondToClient(fd);
}

void Messenger::ErrBadChanMask(int fd) {
  _prefix = SERVER;
  _param = ERR_BADCHANMASK + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "Bad Channel Mask";
  printRed("ErrBadChanMask");
  addRespondToClient(fd);
}

void Messenger::ErrChanOPrivsNeeded(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_CHANOPRIVSNEEDED + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "You're not channel operator";
  printRed("ErrChanOPrivsNeeded");
  addRespondToClient(fd);
}

void Messenger::ErrUModeUnknownFlag(int fd) {
  Client* client = Server::_clientFds[fd];

  _prefix = SERVER;
  _param = ERR_UMODEUNKNOWNFLAG + " " + client->getNickname();
  _trailing = "Unknown MODE flag";
  printRed("ErrUModeUnknownFlag");
  addRespondToClient(fd);
}

void Messenger::ErrUsersDontMatch(int fd) {
  Client* client = Server::_clientFds[fd];

  _prefix = SERVER;
  _param = ERR_USERSDONTMATCH + " " + client->getNickname();
  _trailing = "Cant change mode for other users";
  printRed("ErrUsersDontMatch");
  addRespondToClient(fd);
}

// "<client> <target chan> :Key is not well-formed"
void Messenger::ErrInvalidKey(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = ERR_INVALIDKEY + " " + channel;
  _trailing = "Key is not well-formed [0-9] (maximum length: 8)";
  printRed("ErrInvalidKey");
  addRespondToClient(fd);
}

// :<server> 696 <nick> <channel> <mode> * : <description>
void Messenger::ErrInvalidModeParam(int fd, const std::string& channel,
                                    const char& mode) {
  _prefix = SERVER;
  _param = ERR_INVALIDMODEPARAM + " " + Server::_clientFds[fd]->getNickname() +
           channel + " " + mode + " *";
  printRed("ErrInvalidModeParam");
  addRespondToClient(fd);
}

// unexpected behaviour 에러
void Messenger::ErrUnexpected() { printRed("Unexpected behaviour"); }