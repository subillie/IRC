#include "../RequestHandler.hpp"

// /topic <channel> [<topic>]

void RequestHandler::topic() {
  // parameter가 없을 때
  if (_token.size() == 1) {
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }

  // 해당하는 채널이 없을 때
  const std::string& channel = _token[1];
  if (Server::_channelNames.find(channel) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, channel);
    return;
  }

  Channel* chanToTopic = Server::_channelNames[channel];
  std::set<std::string> memberList = chanToTopic->getMembers();
  std::set<std::string> opList = chanToTopic->getOps();
  const std::string& nick = _client->getNickname();

  // Topic을 설정한 사용자가 해당 채널에 없을 때
  if (!chanToTopic->isMember(nick)) {
    _msg.ErrNotOnChannel(_fd, nick);
    return;
  }

  // Topic을 설정한 사용자가 권한이 없을 때 (모드 +t일 때만 확인)
  if (chanToTopic->isMode('t') && !chanToTopic->isOp(nick)) {
    _msg.ErrChanOPrivsNeeded(_fd, channel);
    return;
  }

  // Check topic
  if (_token.size() == 2) {
    if (chanToTopic->getTopic().empty()) {
      _msg.RplNoTopic(_fd, channel);
      return;
    }
    _msg.RplTopic(_fd, channel, chanToTopic->getTopic());
    return;
  }

  // 전에 있던 topic과 동일할 때 무시
  joinTrailing(2);
  const std::string newtopic = _msg.getTrailing();
  if (newtopic == chanToTopic->getTopic()) {
    return;
  }

  // 채널 member에 topic 전송
  _msg.setPrefix(_client->getPrefix());
  _msg.setParam("TOPIC " + channel);
  _msg.addReplyToChannel(chanToTopic);
  chanToTopic->setTopic(newtopic);
}