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
  std::string nickname = _client->getNickname();
  std::string prefix = _client->getPrefix();
  std::set<std::string> channels = _client->getChannels();
  std::set<std::string>::iterator chanIter = channels.begin();
  for (; chanIter != channels.end(); chanIter++) {
    Channel* channel = Server::_channelNames[*chanIter];

    // 채널에 있는 모든 멤버들에게 메시지 전송
    std::set<std::string> members = channel->getMembers();
    std::set<std::string>::iterator membIter = members.begin();
    for (; membIter != members.end(); membIter++) {
      int fd = Server::_clientNicks[*membIter]->getFd();
      _msg.setPrefix(prefix + " QUIT");
      _msg.setParam("Quit");
      _msg.setTrailing(reason);
      _msg.sendToClient(fd);
    }
    channel->removeMember(nickname);
    channel->removeOp(nickname);
    channel->removeInvitee(nickname);

    // 채널에 멤버가 없으면 채널 삭제
    if (channel->getMembers().empty()) {
      Server::_channelNames.erase(*chanIter);
      delete channel;
      channel = NULL;
    }
  }
  _msg.setParam("ERROR");
  _msg.setTrailing("Closing link: (" + Server::_clientFds[_fd]->getHostname() +
                   ") [Quit: " + reason + "]");
  _msg.sendToClient(_fd);

  throw "Client quit";
}
