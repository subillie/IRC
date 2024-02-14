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
  addRespondToClient(fd);
}

void Messenger::RplYourHost(int fd) {
  _prefix = SERVER;
  _param = RPL_YOURHOST + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "Your host is " + SERVER + ", running version " + VERSION;
  printRed("RplYourHost");
  addRespondToClient(fd);
}
void Messenger::RplCreated(int fd) {
  _prefix = SERVER;
  _param = RPL_CREATED + " " + Server::_clientFds[fd]->getNickname();
  _trailing = "This server was created " + Server::_serverCreated;
  printRed("RplCreated");
  addRespondToClient(fd);
}

void Messenger::RplMyinfo(int fd) {
  _prefix = SERVER;
  _param = RPL_MYINFO + " " + Server::_clientFds[fd]->getNickname() + " " +
           SERVER + " " + VERSION + " " + AVAILABLE_USER_MODES + " " +
           AVAILABLE_CHAN_MODES;
  printRed("RplMyinfo");
  addRespondToClient(fd);
}

void Messenger::RplISupport(int fd) {
  _prefix = SERVER;
  _param = RPL_ISUPPORT + " " + Server::_clientFds[fd]->getNickname() + " " +
           ISUPPORT_PARAMS;
  _trailing = "are supported by this server";
  printRed("RplISupport");
  addRespondToClient(fd);
}

void Messenger::RplUModeIs(int fd, const std::string& usermode) {
  _prefix = SERVER;
  _param = RPL_UMODEIS + " " + Server::_clientFds[fd]->getNickname() + " " +
           usermode;
  printRed("RplUModeIs");
  addRespondToClient(fd);
}

void Messenger::RplEndOfWho(int fd, const std::string& mask) {
  _prefix = SERVER;
  _param =
      RPL_ENDOFWHO + " " + Server::_clientFds[fd]->getNickname() + " " + mask;
  _trailing = "End of /WHO list";
  printRed("RplEndOfWho");
  addRespondToClient(fd);
}

void Messenger::RplEndOfWhoIs(int fd, const std::string& client) {
  _prefix = SERVER;
  _param = RPL_ENDOFWHOIS + " " + Server::_clientFds[fd]->getNickname() + " " +
           client;
  _trailing = "End of /WHOIS list";
  printRed("RplEndOfWhoIs");
  addRespondToClient(fd);
}

void Messenger::RplChannelModeIs(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_CHANNELMODEIS + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  std::set<char> chanModes = Server::_channelNames[channel]->getModes();
  _trailing = "+";
  for (std::set<char>::iterator it = chanModes.begin(); it != chanModes.end();
       ++it)
    _trailing += *it;
  printRed("RplChannelModeIs");
  addRespondToClient(fd);
}

void Messenger::RplNoTopic(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param =
      RPL_NOTOPIC + " " + Server::_clientFds[fd]->getNickname() + " " + channel;
  _trailing = "No topic is set";
  printRed("RplNoTopic");
  addRespondToClient(fd);
}

void Messenger::RplCreationTime(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_CREATIONTIME + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel + " " +
           Server::_channelNames[channel]->getCreationTime();
  printRed("RplCreationTime");
  addRespondToClient(fd);
  RplCreated(fd);
}

void Messenger::RplTopic(int fd, const std::string& channel,
                         const std::string& topic) {
  _prefix = SERVER;
  _param =
      RPL_TOPIC + " " + Server::_clientFds[fd]->getNickname() + " " + channel;
  _trailing = topic;
  printRed("RplTopic");
  addRespondToClient(fd);
}

void Messenger::RplInviteList(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_INVITELIST + " " + Server::_clientFds[fd]->getNickname() + " " +
           channel;
  printRed("RplInviteList");
  addRespondToClient(fd);
}

void Messenger::RplInviting(int fd, const std::string& invitee,
                            const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_INVITING + " " + Server::_clientFds[fd]->getNickname() + " " +
           invitee + " " + channel;
  printRed("RplInviting");
  addRespondToClient(fd);
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
  addRespondToClient(fd);
}

void Messenger::RplNamReply(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_NAMREPLY + " " + Server::_clientFds[fd]->getNickname() + " = " +
           channel;
  printRed("RplNamReply");
  addRespondToClient(fd);
}

void Messenger::RplEndOfNames(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_ENDOFNAMES + " " + Server::_clientFds[fd]->getNickname() + " " +
           channel;
  _trailing = "End of /NAMES list";
  printRed("RplEndOfNames");
  addRespondToClient(fd);
}

void Messenger::RplEndOfBanList(int fd, const std::string& channel) {
  _prefix = SERVER;
  _param = RPL_ENDOFBANLIST + " " + Server::_clientFds[fd]->getNickname() +
           " " + channel;
  _trailing = "End of channel ban list";
  printRed("RplEndOfBanList");
  addRespondToClient(fd);
}