#include "../RequestHandler.hpp"

// MODE <target> [<modestring> [<mode arguments>...]]
void RequestHandler::mode() {
  if (_token.size() < 2) {
    _msg.ErrUnexpected(_fd);
    return;  // 이런 경우는 없을 것 같긴 하지만 일단 예외처리
  }
  // 채널모드인지 유저모드인지 확인
  _token[1][0] == '#' ? channelMode(_token[1]) : userMode(_token[1]);
}

// USER MODE
void RequestHandler::userMode(const std::string& target) {
  const std::string& nick = _client->getNickname();

  // 존재하지 않는 닉네임이면
  if (Server::_clientNicks.find(target) == Server::_clientNicks.end()) {
    _msg.ErrNoSuchNick(_fd, target);
    return;
  }
  // 명령어를 보낸 유저와 닉네임이 다르면
  if (target != _client->getNickname()) {
    _msg.ErrUsersDontMatch(_fd);
    return;
  }
  // <modestring> 이 없으면
  if (_token.size() == 2) {
    _msg.RplUModeIs(_fd, _client->getMode());
    return;
  }
  // <modestring> 지원하지 않는 모드는 에러 (일단 +i 외에는 다 에러)
  if (_token[2].length() > 1 &&
      AVAILABLE_USER_MODES.find(_token[2][1]) != std::string::npos) {
    _msg.setPrefix(_client->getPrefix());
    _msg.setParam("MODE " + nick);
    _msg.setTrailing(_token[2]);
    _msg.sendToClient(_fd);
    _client->setMode(_token[2]);
  } else {
    _msg.ErrUModeUnknownFlag(_fd);
  }
}

// CHANNEL MODE
// l은 set할 때만 인자 존재
// para가 있어야하는데 없으면 ERR_INVALIDMODEPARAM
void RequestHandler::channelMode(const std::string& target) {
  const std::string& nick = _client->getNickname();

  if (Server::_channelNames.find(target) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, target);
    return;
  }
  Channel* channel = Server::_channelNames[target];
  // <modestring> 이 없으면
  if (_token.size() < 3) {
    _msg.RplChannelModeIS(_fd, target);
    return;
  }
  // operator가 아니면
  if (!channel->isOp(nick)) {
    _msg.ErrChanOPrivsNeeded(_fd, target);
    return;
  }
  const std::string& modestring = _token[2];
  // i, t, k, l, o 외엔 모두 에러
  if (modestring.length() > 2 ||
      modestring.find_first_not_of(AVAILABLE_CHAN_MODES + "o", 1) !=
          std::string::npos) {
    _msg.ErrUnknownMode(_fd, modestring);
    return;
  }
  _msg.setPrefix(_client->getPrefix());
  _msg.setParam("MODE " + target + " " + modestring);
  switch (modestring[1]) {
    case CLIENT_LIMIT_CHANNEL:
      limitMode(channel, modestring);
      break;
    case INVITE_ONLY_CHANNEL:
      inviteMode(channel, modestring);
      break;
    case PROTECTED_TOPIC:
      topicMode(channel, modestring);
      break;
    case KEY_CHANNEL:
      keyMode(channel, modestring);
      break;
    case 'o':
      handleOpMode(channel, modestring);
      break;
  }
}

// MODE +o <nick> || MODE -o <nick>
void RequestHandler::handleOpMode(Channel* channel,
                                  const std::string& modestring) {
  // 인자 없을 때
  if (_token.size() < 4) {
    _msg.setTrailing("You must specify a parameter for mode o");
    _msg.ErrInvalidModeParam(_fd, channel->getName(), modestring[1]);
    return;
  }
  const std::string& nick = _token[3];
  // 방에 없는 닉네임이면 401
  if (!channel->isMember(nick)) {
    _msg.ErrNoSuchNick(_fd, nick);
    return;
  }
  // 이미 오퍼레이터인 유저 추가하거나 오퍼레이터가 아닌 유저 빼려고 할 때 리턴
  if ((modestring == "+o" && channel->isOp(nick)) ||
      (modestring == "-o" && !channel->isOp(nick)))
    return;
  // MODE <channelname> <modestring> :<nick>
  _msg.setTrailing(nick);
  modestring == "+o" ? channel->addOp(nick) : channel->removeOp(nick);
  channel->sendToAll(_msg);
}

void RequestHandler::limitMode(Channel* channel,
                               const std::string& modestring) {
  const std::string& channelName = channel->getName();
  // MODE +l <number>
  if (modestring == "+l") {
    // 인자가 없으면
    if (_token.size() < 4) {
      _msg.setTrailing("You must specify a parameter for mode l");
      _msg.ErrInvalidModeParam(_fd, channelName, CLIENT_LIMIT_CHANNEL);
      return;
    }
    const std::string& limitStr = _token[3];
    size_t limit = atoi(limitStr.c_str());
    if (limitStr.find_first_not_of(DIGIT) != std::string::npos || limit < 1) {
      _msg.setTrailing("Invalid parameter for mode l");
      _msg.ErrInvalidModeParam(_fd, channelName, CLIENT_LIMIT_CHANNEL);
      return;
    }
    // 이미 설정된 제한인원과 동일하면 리턴
    if (limit == channel->getLimit()) return;
    // MODE #hi +l :10
    _msg.setTrailing(limitStr);
    channel->setLimit(limit);
    channel->addMode(CLIENT_LIMIT_CHANNEL);
    // MODE -l
  } else if (modestring == "-l") {
    // 해당 모드 없으면 리턴
    if (!channel->isMode(CLIENT_LIMIT_CHANNEL)) return;
    // MODE #hi :-l
    _msg.setParam("MODE " + channelName);
    _msg.setTrailing("-l");
    channel->setLimit(0);
    channel->removeMode(CLIENT_LIMIT_CHANNEL);
  }
  channel->sendToAll(_msg);
}

// i, t는 항상 인자 없음
// 응답 메시지 :one!root@127.0.0.1 MODE <channel> :<modestring>
void RequestHandler::topicMode(Channel* channel,
                               const std::string& modestring) {
  // 이미 해당 모드가 있거나 없으면 응답 없이 리턴
  if ((modestring == "+t" && channel->isMode(PROTECTED_TOPIC)) ||
      (modestring == "-t" && !channel->isMode(PROTECTED_TOPIC)))
    return;
  modestring == "+t" ? channel->addMode(PROTECTED_TOPIC)
                     : channel->removeMode(PROTECTED_TOPIC);
  _msg.setParam("MODE " + channel->getName());
  _msg.setTrailing(modestring);
  channel->sendToAll(_msg);
}

void RequestHandler::inviteMode(Channel* channel,
                                const std::string& modestring) {
  // 이미 해당 모드가 있거나 없으면 응답 없이 리턴
  if ((modestring == "+i" && channel->isMode(INVITE_ONLY_CHANNEL)) ||
      (modestring == "-i" && !channel->isMode(INVITE_ONLY_CHANNEL)))
    return;
  modestring == "+i" ? channel->addMode(INVITE_ONLY_CHANNEL)
                     : channel->removeMode(INVITE_ONLY_CHANNEL);
  _msg.setParam("MODE " + channel->getName());
  _msg.setTrailing(modestring);
  channel->sendToAll(_msg);
}

// k 는 항상 인자 존재
void RequestHandler::keyMode(Channel* channel, const std::string& modestring) {
  if (_token.size() < 4) {
    _msg.setTrailing("You must specify a parameter for mode k");
    _msg.ErrInvalidModeParam(_fd, channel->getName(), KEY_CHANNEL);
    return;
  }
  const std::string& key = _token[3];
  // 비밀번호 형식(8자리 이내 숫자)에 어긋나면 에러
  if (key.find_first_not_of(DIGIT) != std::string::npos || key.length() > 8) {
    _msg.ErrInvalidKey(_fd, channel->getName());
    return;
  }

  if (modestring == "+k") {
    // 같은 키로 바꾸려고 하면 그냥 리턴
    if (channel->getPassword() == key) return;
    channel->addMode(KEY_CHANNEL);
    channel->setPassword(key);
  } else if (modestring == "-k") {
    // -k 인데 키가 다르면 에러
    if (channel->getPassword() != key) {
      _msg.ErrKeySet(_fd, channel->getName());
      return;
    }
    channel->removeMode(KEY_CHANNEL);
    channel->setPassword("");
  }
  _msg.setTrailing(channel->getPassword());
  channel->sendToAll(_msg);
}
