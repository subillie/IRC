#include "../RequestHandler.hpp"

void RequestHandler::kick() {
  if (_token.size() < 3) {  // parameter가 없을 경우
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }
  if (_token[1][0] != '#') {
    // 채널 형식이 올바르지 않을 경우
    _msg.ErrBadChanMask(_fd);
    return;
  }
  // 해당하는 채널이 없을 경우
  if (Server::_channelNames.find(_token[1]) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, _token[1]);
    return;
  }
  Channel *chanToKick = Server::_channelNames[_token[1]];
  std::set<std::string> memberList = chanToKick->getMembers();
  std::set<std::string> opList = chanToKick->getOps();
  // Kick을 요청한 사용자가 해당 채널에 없을 경우
  if (memberList.find(_client->getNickname()) == memberList.end()) {
    _msg.ErrNotOnChannel(_fd, _client->getNickname());
    return;
    // Kick을 요청한 사용자가 권한이 없을 경우
  } else if (opList.find(_client->getNickname()) == opList.end()) {
    _msg.ErrChanOPrivsNeeded(_fd, _client->getNickname());
    return;
  }
  std::stringstream ss(_token[2]);
  std::string target;
  while (std::getline(ss, target, ',')) {
    // 해당 유저가 채널에 없을 경우
    if (memberList.find(target) == memberList.end()) {
      _msg.ErrUserNotInChannel(_fd, target, _token[1]);
    } else {
      std::set<std::string>::const_iterator it;
      for (it = memberList.begin(); it != memberList.end(); ++it) {
        _msg.setPrefix(_client->getNickname() + "!" + _client->getUsername() +
                       "@" + _client->getHostname());
        _msg.setParam("KICK " + _token[1] + " " + target);
        std::string trailing = "";
        for (size_t i = 3; i < _token.size(); ++i) {
          trailing += _token[i];
          if (i < _token.size() - 1) {
            trailing += " ";
          }
          _msg.setTrailing(trailing);
        }
        _msg.sendToClient(Server::_clientNicks[*it]->getFd());
      }
      chanToKick->removeMember(target);
      chanToKick->removeOp(target);
    }
  }
}
