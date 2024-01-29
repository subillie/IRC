#include "../RequestHandler.hpp"

void RequestHandler::privmsg() {
  // parameter가 없음
  if (_token.size() == 1) {
    _msg.ErrUnexpected(_fd);
    return;
  }
  // parameter 갯수가 부족할 떄
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
    std::cout << target << std::endl;
    if (target[0] == '#') {
      printBlue(target);
      if (Server::_channelNames.find(target) == Server::_channelNames.end()) {
        _msg.ErrCannotSendToChan(_fd);  // target에 해당하는 채널이 없음
        continue;
      }
      Channel* chanToSend = Server::_channelNames[target];
      std::set<std::string> memberList = chanToSend->getMembers();
      if (memberList.find(_client->getNickname()) == memberList.end()) {
        _msg.ErrCannotSendToChan(_fd);  // 본인 속한 채널이 아님
        continue;
      }
      std::set<std::string>::const_iterator it;
      for (it = memberList.begin(); it != memberList.end(); ++it) {
        if (*it != _client->getNickname()) {
          _msg.setPrefix("PRIVMSG");
          _msg.setParam(_client->getNickname());
          _msg.setTrailing(_token[2]);
          _msg.sendToClient(Server::_clientNicks[*it]->getFd());
        }
      }
    } else {
      if (Server::_clientNicks.find(target) == Server::_clientNicks.end()) {
        _msg.ErrNoSuchNick(_fd, target);  // 등록된 닉네임이 없음
        continue;
      }
      _msg.setPrefix("PRIVMSG");
      _msg.setParam(_client->getNickname());
      _msg.setTrailing(_token[2]);
      _msg.sendToClient(Server::_clientNicks[_token[1]]->getFd());
    }
  }
}