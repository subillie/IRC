#include "../RequestHandler.hpp"

// /part <channel>{,<channel>} [<reason>]
void RequestHandler::part() {
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }

  std::stringstream ss(_token[1]);
  std::string channelName;
  std::vector<std::string> channels;
  while (getline(ss, channelName, ',')) {
    channels.push_back(channelName);
  }
  std::string reason;
  if (_token.size() == 3) {
    reason = _token[2];
  }

  std::vector<std::string>::iterator iter = channels.begin();
  for (; iter != channels.end(); ++iter) {
    channelName = *iter;

    // client가 입력한 채널명이 #으로 시작하지 않는다면 #을 붙여줌
    if (channelName[0] != '#') {
      channelName = '#' + channelName;
    }
    // 채널이 존재하지 않을 경우
    if (Server::_channelNames.find(channelName) ==
        Server::_channelNames.end()) {
      _msg.ErrNoSuchChannel(_fd, channelName);
      continue;
    }
    Channel *chanToLeave = Server::_channelNames[channelName];
    channelName = chanToLeave->getName();
    std::set<std::string> membList = chanToLeave->getMembers();

    // client가 해당 채널 멤버가 아닐 경우
    if (membList.find(_client->getNickname()) == membList.end()) {
      _msg.ErrNotOnChannel(_fd, channelName);
      continue;
      // 멤버일 경우 채널에서 client 퇴장
    } else {
      chanToLeave->removeMember(_client->getNickname());
      chanToLeave->removeOp(_client->getNickname());
      chanToLeave->removeInvitee(_client->getNickname());
      _client->removeChannel(channelName);

      _msg.setPrefix(_client->getNickname() + "!" + _client->getUsername() +
                     "@" + _client->getHostname());
      _msg.setParam("PART " + channelName);
      if (!reason.empty()) {
        _msg.setTrailing(reason);
      }

      std::set<std::string>::const_iterator member;
      for (member = membList.begin(); member != membList.end(); ++member) {
        _msg.sendToClient(Server::_clientNicks[*member]->getFd());
      }
    }
  }
}