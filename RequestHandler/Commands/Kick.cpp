#include "../RequestHandler.hpp"

// /kick <channel> <user> *( "," <user> ) [<comment>]

void RequestHandler::kick() {
  // parameter가 없을 때
  if (_token.size() < 3) {
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }

  const std::string& channelName = _token[1];
  // 채널 형식이 올바르지 않을 때
  if (channelName[0] != '#') {
    _msg.ErrBadChanMask(_fd);
    return;
  }

  // 해당 채널이 존재하지 않을 때
  if (Server::_channelNames.find(channelName) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, channelName);
    return;
  }

  Channel* chanToKick = Server::_channelNames[channelName];
  const std::string& nick = _client->getNickname();
  std::set<std::string> memberList = chanToKick->getMembers();
  std::set<std::string> opList = chanToKick->getOps();
  // Kick을 요청한 사용자가 해당 채널에 없을 때
  if (!chanToKick->isMember(nick)) {
    _msg.ErrNotOnChannel(_fd, nick);
    return;
    // Kick을 요청한 사용자가 권한이 없을 때
  } else if (!chanToKick->isOp(nick)) {
    _msg.ErrChanOPrivsNeeded(_fd, chanToKick->getName());
    return;
  }

  std::stringstream ss(_token[2]);
  std::string target;
  while (std::getline(ss, target, ',')) {
    // 해당 유저가 채널에 없을 때
    if (!chanToKick->isMember(target)) {
      _msg.ErrUserNotInChannel(_fd, target, channelName);
    } else {
      _msg.setPrefix(_client->getPrefix());
      _msg.setParam("KICK " + channelName + " " + target);
      std::string trailing;
      for (size_t i = 3; i < _token.size(); ++i) {
        trailing += _token[i];
        if (i < _token.size() - 1) trailing += " ";
        _msg.setTrailing(trailing);
      }
      _msg.addRespondToChannel(chanToKick);
      // chanToKick->sendToAll(_msg);
      Server::_clientNicks[target]->leaveChannel(chanToKick);
    }
  }
}
