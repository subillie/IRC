#include "RequestHandler.hpp"

void RequestHandler::cap() {
  Messenger msg;

  if (_token[1] == "LS") {
    msg.setPrefix(SERVER);
    msg.setParam("CAP * LS :");
    msg.sendToClient(_fd);
  }
  // else if (_token[1] == "END") {
  //   // start registration
  // }
}

void RequestHandler::nick() {
  Messenger msg;

  if (_token.size() != 2) {
    msg.ErrNoNickNameGiven(_fd);
    return;
  } else if (Server::_clientNicks.find(_token[1]) !=
             Server::_clientNicks.end()) {
    msg.ErrNickNameInUse(_fd);
    return;
  } else {
    if (std::isdigit(_token[1][0])) {
      msg.ErrErroneusNickName(_fd);
      return;
    }
    size_t pos = _token[1].find_first_not_of(
        LOWERCASE + UPPERCASE + SPECIAL_CHAR + DIGIT, 1);
    if (pos != std::string::npos) {
      msg.ErrErroneusNickName(_fd);
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
  Messenger msg;
  // USER <username> 0 * <realname> 외의 형식 있는지 확인해야함
  if (!_client->getUsername().empty()) {
    msg.ErrUnexpected(_fd);
    return;
  }
  // : 뒤에는 하나로 침
  if (_token.size() != 5) {
    msg.ErrNeedMoreParams(_fd, "USER");
    return;
  }
  std::string username = _token[1];
  std::string hostname = _token[4];
  // std::map<int, Client*>::iterator iter = Server::_clientFds.begin();
  for (std::map<int, Client*>::iterator iter = Server::_clientFds.begin();
       iter != Server::_clientFds.end(); iter++) {
    if (iter->second->getUsername() == username) {
      msg.ErrAlreadyRegistered(_fd);
      return;
    }
  }
  // max 길이 정해야 함
  bool isOutOfLen = (username.length() < 1 || username.length() > 12);
  bool isSpecialChar = (username.find_first_not_of("\0@") == std::string::npos);
  if (isOutOfLen || isSpecialChar) {
    msg.ErrUnexpected(_fd);
    return;
  }
  _client->setUsername(username);
  _client->setHostname(hostname);
  if (!(_client->getPassword().empty() || _client->getNickname().empty() ||
        _client->getUsername().empty())) {
    _client->setIsRegisterd(true);
  } else {
    msg.ErrUnexpected(_fd);
    return;
  }
  std::cout << *_client;  // debug
  msg.RplWelcome(_fd);
}

// PASS <password>
void RequestHandler::pass() {
  Messenger msg;
  // 인자가 없을 때
  if (_token.size() < 2) {
    msg.ErrNeedMoreParams(_fd, "PASS");
    return;
    // 비번 틀림 ERR_PASSWDMISMATCH => close connection
  } else if (_token[1] != _password) {
    msg.ErrPasswdMismatch(_fd);
    return;
    // 이미 가입 됨 ERR_ALREADYREGISTERED
  } else if (_client->getIsRegistered()) {
    msg.ErrAlreadyRegistered(_fd);
    return;
  }
  _client->setPassword(_token[1]);
}

void RequestHandler::join() {
  Messenger msg;
  // /join #채널명 <암호> // 각각 여러 개 들어갈 수 있음
  // 인자가 없으면 ERR_NEEDMOREPARAMS
  if (_token.size() < 2) {
    msg.ErrNeedMoreParams(_fd);
    return;
  }
  std::vector<std::string> channels;
  std::stringstream ss;
  while (getline(ss, _token[1], ',')) {
    channels.push_back(_token[1]);
  }

  // TODO: no such channel로 처리하는 게 맞나?
  // 채널명이 유효하지 않으면 ERR_NOSUCHCHANNEL
  std::vector<std::string>::iterator iter = channels.begin();
  for (; iter != channels.end(); iter++) {
    if (iter->empty() || (*iter)[0] != '#' ||
        iter->find_first_not_of(LOWERCASE + UPPERCASE + SPECIAL_CHAR + DIGIT) !=
            std::string::npos) {
      // msg.ErrNoSuchChannel();
      return;
    }
  }
  // // 채널이 없으면 생성
  // if (Server::_channelNames.find(channel) == Server::_channelNames.end()) {
  //   Server::_channelNames[channel] = new Channel(channel);
  // } else {
  //   // 채널에 이미 참가 중이면 ERR_TOOMANYCHANNELS
  //   if (Server::_channelNames[channel]->getClients().find(_client) !=
  //       Server::_channelNames[channel]->getClients().end()) {
  //     msg.ErrTooManyChannels();
  //     return;
  //   }
  // }

  msg.sendToClient(_fd);
}

void RequestHandler::privmsg() {
  Messenger msg;

  const std::string response =
      "Hello from the server!";  // client connection test
  msg.sendToClient(_fd);
}

void RequestHandler::kick() {}

void RequestHandler::invite() {}

void RequestHandler::topic() {}

void RequestHandler::mode() {}

void RequestHandler::pong() {
  Messenger msg;
  if (_token.size() < 2) {
    msg.ErrNeedMoreParams(_fd, "PONG");
    return;
  } else if (_token[1].empty()) {
    msg.ErrNoOrigin(_fd);
    return;
  }
  msg.setPrefix(SERVER);
  msg.setParam("PONG " + SERVER);
  msg.setTrailing(_token[1]);
  msg.sendToClient(_fd);
}
