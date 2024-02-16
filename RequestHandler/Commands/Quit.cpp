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

  // Reply를 보낼 client 명단 만듦
  std::set<std::string> clientsToReply;
  std::set<std::string> channels = _client->getChannels();
  std::set<std::string>::iterator chanIter, memIter;
  for (chanIter = channels.begin(); chanIter != channels.end(); chanIter++) {
    Channel *channel = Server::_channelNames[*chanIter];
    std::set<std::string> members = channel->getMembers();
    for (memIter = members.begin(); memIter != members.end(); memIter++) {
      clientsToReply.insert(*memIter);
    }
    _client->leaveChannel(channel);  // Quit
  }

  // 명단에 있는 모든 client에게 reply를 보냄
  for (memIter = clientsToReply.begin(); memIter != clientsToReply.end();
       memIter++) {
    _msg.setPrefix(_client->getPrefix() + " QUIT");
    _msg.setParam("Quit");
    _msg.setTrailing(reason);
    _msg.addReplyToClient(Server::_clientNicks[*memIter]->getFd());
  }

  _msg.setParam("ERROR");
  _msg.setTrailing("Closing link: (" + Server::_clientFds[_fd]->getHostname() +
                   ") [Quit: " + reason + "]");
  _msg.addReplyToClient(_fd);

  _client->setIsQuit(true);
  printRed("Client Quit");
}
