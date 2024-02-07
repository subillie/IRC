#include "../RequestHandler.hpp"

// /msg <channel>/<nick>,... <text to be sent>

void RequestHandler::privmsg() {
  // parameter가 없을 때
  if (_token.size() == 1) {
    _msg.ErrUnexpected();
    return;
  }

  // parameter 개수가 부족할 떄
  if (_token.size() < 3) {
    if (_token[1][0] == ':')
      _msg.ErrNoRecipient(_fd);  // 수신자가 없음
    else if (_token[1][0] != ':')
      _msg.ErrNoTextToSend(_fd);  // 메세지가 없음
    return;
  }

  std::stringstream ss(_token[1]);
  std::string target;
  while (std::getline(ss, target, ',')) {
    if (target[0] == '#') {
      // target에 해당하는 채널이 없을 때
      if (Server::_channelNames.find(target) == Server::_channelNames.end()) {
        _msg.ErrCannotSendToChan(_fd, target);
        continue;
      }
      // 본인 속한 채널이 아닐 때
      Channel* chanToSend = Server::_channelNames[target];
      std::set<std::string> memberList = chanToSend->getMembers();
      if (memberList.find(_client->getNickname()) == memberList.end()) {
        _msg.ErrCannotSendToChan(_fd, target);
        continue;
      }

      std::istringstream iss(_token[2]);
      std::string textType;
      iss >> textType;
      if (textType == "!BGP") {
        bgp(memberList);
        continue;
      } else if (textType == "!RPS") {
        rps(memberList);
        continue;
      }

      std::set<std::string>::const_iterator it;
      for (it = memberList.begin(); it != memberList.end(); ++it) {
        if (*it != _client->getNickname()) {
          _msg.setPrefix(_client->getPrefix());
          _msg.setParam("PRIVMSG " + _token[1]);
          _msg.setTrailing(_token[2]);
          _msg.sendToClient(Server::_clientNicks[*it]->getFd());
        }
      }
    } else {
      // 등록된 닉네임이 없을 때
      if (Server::_clientNicks.find(target) == Server::_clientNicks.end()) {
        _msg.ErrNoSuchNick(_fd, target);
        continue;
      }
      _msg.setPrefix(_client->getPrefix());
      _msg.setParam("PRIVMSG " + _token[1]);
      _msg.setTrailing(_token[2]);
      _msg.sendToClient(Server::_clientNicks[_token[1]]->getFd());
    }
  }
}