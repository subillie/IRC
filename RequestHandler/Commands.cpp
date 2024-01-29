#include "RequestHandler.hpp"

void RequestHandler::cap() {
  if (_token[1] == "LS") {
    _msg.setPrefix(SERVER);
    _msg.setParam("CAP * LS :");
    _msg.sendToClient(_fd);
  }
  // else if (_token[1] == "END") {
  //   // start registration
  // }
}

void RequestHandler::nick() {
  if (_token.size() != 2) {
    _msg.ErrNoNickNameGiven(_fd);
    return;
  } else if (Server::_clientNicks.find(_token[1]) !=
             Server::_clientNicks.end()) {
    _msg.ErrNickNameInUse(_fd);
    return;
  } else {
    if (std::isdigit(_token[1][0])) {
      _msg.ErrErroneusNickName(_fd);
      return;
    }
    size_t pos = _token[1].find_first_not_of(
        LOWERCASE + UPPERCASE + SPECIAL_CHAR + DIGIT, 1);
    if (pos != std::string::npos) {
      _msg.ErrErroneusNickName(_fd);
      return;
    }
  }
  // nickname 설정이 되어 있을 경우
  if (_client->getNickname() != "") {
    Server::_clientNicks.erase(_client->getNickname());
  }
  _client->setNickname(_token[1]);
  Server::_clientNicks[_token[1]] = _client;
}

void RequestHandler::user() {
  // USER <username> 0 * <realname> 외의 형식 있는지 확인해야함
  if (!_client->getUsername().empty()) {
    _msg.ErrUnexpected(_fd);
    return;
  }
  // : 뒤에는 하나로 침
  if (_token.size() != 5) {
    _msg.ErrNeedMoreParams(_fd, "USER");
    return;
  }
  std::string username = _token[1];
  std::string hostname = _token[3];
  if (_client->getIsRegistered()) {
    return;
  }
  // max 길이 정해야 함
  bool isOutOfLen = (username.length() < 1 || username.length() > 12);
  bool isSpecialChar = (username.find_first_not_of("\0@") == std::string::npos);
  if (isOutOfLen || isSpecialChar) {
    _msg.ErrUnexpected(_fd);
    return;
  }
  _client->setUsername(username);
  _client->setHostname(hostname);
  if (!(_client->getPassword().empty() || _client->getNickname().empty() ||
        _client->getUsername().empty())) {
    _client->setIsRegisterd(true);
  } else {
    _msg.ErrUnexpected(_fd);
    return;
  }
  std::cout << *_client;  // debug
  _msg.RplWelcome(_fd);
}

// PASS <password>
void RequestHandler::pass() {
  // 인자가 없을 때
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, "PASS");
    return;
    // 비번 틀림 ERR_PASSWDMISMATCH => close connection
  } else if (_token[1] != _password) {
    _msg.ErrPasswdMismatch(_fd);
    return;
    // 이미 가입 됨 ERR_ALREADYREGISTERED
  } else if (_client->getIsRegistered()) {
    _msg.ErrAlreadyRegistered(_fd);
    return;
  }
  _client->setPassword(_token[1]);
}

void RequestHandler::join() {
  // 인자가 없을 때
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, "JOIN");
    return;
  }

  // /join <channel>{,<channel>} [<key>{,<key>}]
  std::stringstream ss1(_token[1]), ss2(_token[2]);
  std::string channel, password;
  std::map<std::string, std::string> keys;
  while (std::getline(ss1, channel, ',')) {
    std::getline(ss2, password, ',');
    keys[channel] = password;
    std::cout << "channel: " << channel << " (" << channel.length()
              << "), password: " << password << std::endl;  // TODO: debug
  }

  std::map<std::string, std::string>::iterator iter = keys.begin();
  for (; iter != keys.end(); iter++) {
    // TODO: 비밀번호도 SPECIAL_CHAR 확인하기
    // 채널명이 유효하지 않을 때
    if (iter->first.empty() ||
        iter->first.find(SPECIAL_CHAR) != std::string::npos) {
      _msg.ErrBadChanMask(_fd);
      continue;
    }
    // 채널이 없으면 생성
    if (Server::_channelNames.find(iter->first) ==
        Server::_channelNames.end()) {
      Server::_channelNames[iter->first] = new Channel(DEFAULT, iter->first);
    } else {
      Channel* chanToJoin = Server::_channelNames[iter->first];
      std::list<std::string> memberList = chanToJoin->getMembers();
      std::list<std::string>::iterator membIter =
          std::find(memberList.begin(), memberList.end(), iter->first);
      // 이미 참가 중인 채널이면 무시
      if (membIter != memberList.end()) {
        continue;
        // 채널이 존재하고 멤버 명단에 없으면 참가
      } else {
        // 해당 채널이 Key Channel Mode이면 비밀번호 확인
        if (chanToJoin->getMode() == KEY_CHANNEL) {
          if (chanToJoin->getPassword() != iter->second) {
            _msg.ErrBadChannelKey(_fd);
            continue;
          }
          // 해당 채널이 Invite Only Channel Mode이면 초대 리스트에 있는지 확인
        } else if (chanToJoin->getMode() == INVITE_ONLY_CHANNEL) {
          std::list<std::string> inviteeList = chanToJoin->getInvitees();
          if (std::find(inviteeList.begin(), inviteeList.end(),
                        _client->getNickname()) ==
              chanToJoin->getInvitees().end()) {
            _msg.ErrInviteOnlyChan(_fd);
            continue;
          }
          // 해당 채널이 Client Limit Channel Mode이면 인원 제한 확인
        } else if (chanToJoin->getMode() == CLIENT_LIMIT_CHANNEL) {
          if (chanToJoin->getLimit() < chanToJoin->getMembers().size()) {
            _msg.ErrTooManyChannels(_fd);
            continue;
          }
        }
        chanToJoin->addMember(iter->first);
        // 해당 채널에 topic이 존재한다면 topic 전송
        if (!chanToJoin->getTopic().empty()) {
          _msg.RplTopic(_fd, iter->first, chanToJoin->getTopic());
        }
        // 해당 채널의 모든 유저에게 join 메시지 전송
        for (membIter = memberList.begin(); membIter != memberList.end();
             membIter++) {
          _msg.RplNamReply(_fd, iter->first, *membIter);
          _msg.RplEndOfNames(_fd, iter->first);
        }
      }
    }
  }

  _msg.sendToClient(_fd);
}

void RequestHandler::privmsg() {
  const std::string response =
      "Hello from the server!";  // client connection test
  _msg.sendToClient(_fd);
}

void RequestHandler::kick() {}

void RequestHandler::invite() {}

void RequestHandler::topic() {}

void RequestHandler::pong() {
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, "PONG");
    return;
  } else if (_token[1].empty()) {
    _msg.ErrNoOrigin(_fd);
    return;
  }
  _msg.setPrefix(SERVER);
  _msg.setParam("PONG " + SERVER);
  _msg.setTrailing(_token[1]);
  _msg.sendToClient(_fd);
}
