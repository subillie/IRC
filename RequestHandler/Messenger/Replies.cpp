#include "Messenger.hpp"

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

void Messenger::RplISupport(int fd) {
  _prefix = SERVER;
  _param = RPL_ISUPPORT + " " + Server::_clientFds[fd]->getNickname() + " " +
           ISUPPORT_PARAMS;
  _trailing = "are supported by this server";
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

void Messenger::RplEndOfWho(int fd, const std::string& mask) {
  _prefix = SERVER;
  _param =
      RPL_ENDOFWHO + " " + Server::_clientFds[fd]->getNickname() + " " + mask;
  _trailing = "End of /WHO list";
  printRed("RplEndOfWho");
  sendToClient(fd);
}

void Messenger::RplChannelModeIS(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_CHANNELMODEIS + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  std::set<char> chanModes = Server::_channelNames[channel]->getModes();
  _trailing = "+";
  for (std::set<char>::iterator it = chanModes.begin(); it != chanModes.end();
       ++it)
    _trailing += *it;
  printRed("RplChannelModeIS");
  sendToClient(fd);
}

void Messenger::RplNoTopic(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param =
      RPL_NOTOPIC + " " + Server::_clientFds[fd]->getNickname() + " " + channel;
  _trailing = "No topic is set";
  printRed("RplNoTopic");
  sendToClient(fd);
}

void Messenger::RplCreationTime(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_CREATIONTIME + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel + " " +
           Server::_channelNames[channel]->getCreationTime();
  printRed("RplCreationTime");
  sendToClient(fd);
  RplCreated(fd);
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

void Messenger::RplInviting(int fd, const std::string& invitee,
                            const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_INVITING + " " + Server::_clientFds[fd]->getNickname() + " " +
           invitee + " " + channel;
  printRed("RplInviting");
  sendToClient(fd);
}

void Messenger::RplWhoReply(int fd, const std::string& mask,
                            const std::string& channel,
                            const std::string& flag) {
  Client* client = Server::_clientFds[fd];
  _prefix = SERVER;
  _param = RPL_WHOREPLY + " " + client->getNickname() + " " + channel + " " +
           client->getUsername() + " " + client->getHostname() + " " + SERVER +
           " " + mask + " " + flag;
  _trailing = "0 " + client->getRealname();
  printRed("RplWhoReply");
  sendToClient(fd);
}

void Messenger::RplNamReply(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_NAMREPLY + " " + Server::_clientFds[fd]->getNickname() + " = " +
           channel;
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