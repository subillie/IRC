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
    if (channelName[0] != '#') {
      _msg.ErrBadChanMask(_fd);
      continue;
    }
    channels.push_back(channelName);
  }

  std::vector<std::string>::iterator iter = channels.begin();
  for (; iter != channels.end(); ++iter) {
    channelName = *iter;

    // 채널이 존재하지 않을 때
    if (Server::_channelNames.find(channelName) ==
        Server::_channelNames.end()) {
      _msg.ErrNoSuchChannel(_fd, channelName);
      continue;
    }
    Channel *chanToLeave = Server::_channelNames[channelName];
    channelName = chanToLeave->getName();

    // client가 해당 채널 멤버가 아닐 때
    if (!chanToLeave->isMember(_client->getNickname())) {
      _msg.ErrNotOnChannel(_fd, channelName);
      continue;
      // 멤버일 경우 채널에서 client 퇴장
    } else {
      _msg.setPrefix(_client->getPrefix());
      _msg.setParam("PART " + channelName);
      if (_token.size() >= 3) {
        joinTrailing(2);
      }
      // chanToLeave->sendToAll(_msg);
      _msg.addReplyToChannel(chanToLeave);
      _client->leaveChannel(chanToLeave);
    }
  }
}
