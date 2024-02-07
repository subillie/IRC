#include "../RequestHandler.hpp"

// /join <channel>{,<channel>} [<key>{,<key>}]
void RequestHandler::join() {
  // 인자가 없을 때
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, "JOIN");
    return;
  }
  if (_token[1] == " ") {
    return;
  }

  std::stringstream ss1(_token[1]), ss2(_token[2]);
  std::string channel, password;
  std::map<std::string, std::string> keys;
  while (std::getline(ss1, channel, ',')) {
    std::getline(ss2, password, ',');
    keys[channel] = password;
  }

  std::map<std::string, std::string>::iterator iter = keys.begin();
  for (; iter != keys.end(); iter++) {
    const std::string& channelName = iter->first;
    const std::string& channelKey = iter->second;

    // 채널명이 유효하지 않을 때
    if (channelName.empty() || channelName[0] != '#' ||
        channelName.length() > MAX_CHANNEL_LEN) {
      _msg.ErrNoSuchChannel(_fd, channelName);
      continue;
    }

    // 이미 가입한 채널 수가 최대치일 때
    if (_client->isMaxJoined()) {
      _msg.ErrTooManyChannels(_fd, channelName);
      break;
    }

    // 채널이 없으면 생성
    if (isExistingChannel(channelName).empty()) {
      Server::_channelNames[channelName] =
          new Channel(PROTECTED_TOPIC, channelName);
      Server::_channelNames[channelName]->addOp(_client->getNickname());
      addUser(Server::_channelNames[channelName]);
    } else {
      Channel* chanToJoin =
          Server::_channelNames[isExistingChannel(channelName)];
      // 이미 참가 중인 채널이면 무시
      if (chanToJoin->isMember(_client->getNickname())) {
        continue;
        // 채널이 존재하고 멤버 명단에 없으면 참가
      } else {
        // 해당 채널이 Key Channel Mode이면 비밀번호 확인
        if (chanToJoin->isMode(KEY_CHANNEL) &&
            chanToJoin->getPassword() != channelKey) {
          _msg.ErrBadChannelKey(_fd, channelName);
          continue;
        }
        // 해당 채널이 Invite Only Channel Mode이면 초대 리스트에 있는지 확인
        if (chanToJoin->isMode(INVITE_ONLY_CHANNEL) &&
            !chanToJoin->isInvitee(_client->getNickname())) {
          _msg.ErrInviteOnlyChan(_fd, channelName);
          continue;
        }
        // 해당 채널이 Client Limit Channel Mode이면 인원 제한 확인
        // 초대장 받은 유저는 인원 제한 수 상관 없이 입장 가능 함
        if (chanToJoin->isMode(CLIENT_LIMIT_CHANNEL) && chanToJoin->isFull() &&
            !chanToJoin->isInvitee(_client->getNickname())) {
          _msg.ErrChannelIsFull(_fd, channelName);
          continue;
        }
        // 채널에 유저 추가
        addUser(chanToJoin);
      }
    }
  }
}

void RequestHandler::addUser(Channel* chanToJoin) {
  // 채널의 멤버 목록에 유저 추가, 클라이언트의 채널 목록에 채널 추가
  std::string nickname = _client->getNickname();
  std::string channelName = chanToJoin->getName();
  chanToJoin->addMember(nickname);
  _client->addChannel(channelName);

  // 해당 채널에 topic이 존재한다면 topic 전송
  if (!chanToJoin->getTopic().empty()) {
    _msg.RplTopic(_fd, channelName, chanToJoin->getTopic());
  }

  // 해당 채널의 모든 유저에게 join 메시지 전송
  std::set<std::string> memberList = chanToJoin->getMembers();
  std::set<std::string>::const_iterator membIter;

  // one_!root@127.0.0.1 JOIN :#bbbbb
  Messenger joinMsg;
  joinMsg.setPrefix(_client->getPrefix());
  joinMsg.setParam("JOIN");
  joinMsg.setTrailing(channelName);
  chanToJoin->sendToAll(joinMsg);

  // 채널 모든 멤버를 trailing에 담아서 보냄
  std::string trailing;
  for (membIter = memberList.begin(); membIter != memberList.end();
       membIter++) {
    if (chanToJoin->isOp(*membIter)) trailing += "@";
    trailing += *membIter + " ";
  }
  _msg.setTrailing(trailing);
  _msg.RplNamReply(_fd, channelName);
  _msg.RplEndOfNames(_fd, channelName);
}

// 대소문자 구분 없이 이미 있는 채널일 경우 그 채널을 반환
std::string RequestHandler::isExistingChannel(const std::string& channel) {
  std::map<std::string, Channel*>::iterator it;
  for (it = Server::_channelNames.begin(); it != Server::_channelNames.end();
       it++) {
    std::string existingChan = it->second->getName();
    if (channel.length() != existingChan.length()) continue;
    for (size_t i = 0; i <= channel.length(); i++) {
      if (i == channel.length()) return existingChan;
      if (tolower(channel[i]) != tolower(existingChan[i])) break;
    }
  }
  return "";
}