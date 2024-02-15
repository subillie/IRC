#include "../RequestHandler.hpp"

// /quit [<reason>]
void RequestHandler::quit() {
  std::string reason = "";
  if (_token.size() == 1) {
    reason = "leaving";
  }
  for (size_t i = 1; i < _token.size(); i++) {
    reason += _token[i];
    reason += " ";
  }
  reason.erase(reason.find_last_not_of(' ') + 1);

  // client가 참여 중인 모든 채널에 대해
  std::string prefix = _client->getPrefix();
  _msg.addReplyToClient(_fd);
  std::map<int, Client *>::iterator fdIter = Server::_clientFds.begin();
  for (; fdIter != Server::_clientFds.end(); fdIter++) {
    if (isInSameChannel(_client, fdIter->second)) {
      _msg.setPrefix(prefix + " QUIT");
      _msg.setParam("Quit");
      _msg.setTrailing(reason);
      _msg.addReplyToClient(fdIter->first);
    }
  }

  std::set<std::string> channels = _client->getChannels();
  std::set<std::string>::iterator chanToQuit = channels.begin();
  for (; chanToQuit != channels.end(); chanToQuit++) {
    Channel *channel = Server::_channelNames[*chanToQuit];
    _client->leaveChannel(channel);
  }

  _msg.setParam("ERROR");
  _msg.setTrailing("Closing link: (" + Server::_clientFds[_fd]->getHostname() +
                   ") [Quit: " + reason + "]");
  _msg.addReplyToClient(_fd);

  _client->setIsQuit(true);
  printRed("Client Quit");
}
