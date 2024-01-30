#include "../RequestHandler.hpp"

void RequestHandler::topic() {
  // parameter가 없을 경우
  if (_token.size() == 1) {
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }
  // 해당하는 채널이 없을 경우
  if (Server::_channelNames.find(_token[1]) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, _token[1]);
    return;
  }
  Channel *chanToTopic = Server::_channelNames[_token[1]];
  std::set<std::string> memberList = chanToTopic->getMembers();
  std::set<std::string> opList = chanToTopic->getOps();
  // Topic을 설정한 사용자가 해당 채널에 없을 경우
  if (memberList.find(_client->getNickname()) == memberList.end()) {
    _msg.ErrNotOnChannel(_fd, _client->getNickname());
    return;
    // Topic을 설정한 사용자가 권한이 없을 경우
  } else if (opList.find(_client->getNickname()) == opList.end()) {
    _msg.ErrChanOPrivsNeeded(_fd, chanToTopic->getName());
    return;
  }
  // check topic
  if (_token.size() == 2) {
    if (chanToTopic->getTopic().empty()) {
      _msg.RplNoTopic(_fd, chanToTopic->getName());
      return;
    }
    _msg.RplTopic(_fd, chanToTopic->getName(), chanToTopic->getTopic());
    // Rpl_TopicWhoTime(_fd);
    return;
  }
  std::string newtopic;
  for (size_t i = 2; i < _token.size(); ++i) {
    newtopic += _token[i];
    if (i < _token.size() - 1) {
      newtopic += " ";
    }
  }
  // 전에 있던 topic과 동일한 경우 무시
  if (newtopic == chanToTopic->getTopic()) return;
  // 채널 member에 topic 전송
  std::set<std::string>::const_iterator it;
  for (it = memberList.begin(); it != memberList.end(); ++it) {
    _msg.setPrefix(_client->getNickname() + "!" + _client->getUsername() + "@" +
                   _client->getHostname());
    _msg.setParam("TOPIC " + _token[1]);
    _msg.setTrailing(newtopic);
    _msg.sendToClient(Server::_clientNicks[*it]->getFd());
  }
  chanToTopic->setTopic(newtopic);
}