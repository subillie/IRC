#include "RequestHandler.hpp"

void RequestHandler::cap() {
  printDebug("command", _token[0]);
  // Make reply for...
  if (_token[1] == "LS") {  // CAP LS
    sendToClient(_fd, "CAP * LS :");
  } else if (_token[1] == "END") {  // CAP END
    sendToClient(_fd, "");
  }
}

void RequestHandler::nick() {
  if (_token.size() != 2) {
    _error.ErrNoNickNameGiven();
    return;
  } else if (Server::_clientNicks.find(_token[1]) !=
             Server::_clientNicks.end()) {
    _error.ErrNickNameInUse();
    return;
  } else {
    if (std::isdigit(_token[1][0])) {
      _error.ErrErroneusNickName();
      return;
    }
    size_t pos = _token[1].find_first_not_of(
        LOWERCASE + UPPERCASE + SPECIAL_CHAR + DIGIT, 1);
    if (pos != std::string::npos) {
      _error.ErrErroneusNickName();
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
    _error.ErrUnknown();
  }
  // : 뒤에는 하나로 침
  if (_token.size() != 5) {
    _error.ErrNeedMoreParams();
  }
  std::string username = _token[1];
  // std::map<int, Client*>::iterator iter = Server::_clientFds.begin();
  for (std::map<int, Client*>::iterator iter = Server::_clientFds.begin();
       iter != Server::_clientFds.end(); iter++) {
    if (iter->second->getUsername() == username) {
      _error.ErrAlreadyRegistered();
    }
  }
  // max 길이 정해야 함
  bool isOutOfLen = (username.length() < 1 || username.length() > 12);
  bool isSpecialChar = (username.find_first_not_of("\0@") == std::string::npos);
  if (isOutOfLen || isSpecialChar) {
    _error.ErrUnknown();
  }
  _client->setUsername(username);
  printDebug("username", _client->getUsername());
  if (!(_client->getPassword().empty() || _client->getNickname().empty() ||
        _client->getUsername().empty())) {
    _client->setIsRegisterd(true);
  } else {
    _error.ErrUnknown();
  }
  std::cout << *_client;  // print client (for debugging)
}

// PASS <password>
void RequestHandler::pass() {
  // 인자가 없을 때
  if (_token.size() < 2) {
    _error.ErrNeedMoreParams();
    // 비번 틀림 ERR_PASSWDMISMATCH => close connection
  } else if (_token[1] != _password) {
    _error.ErrPasswdMismatch();
    // 이미 가입 됨 ERR_ALREADYREGISTERED
  } else if (_client->getIsRegistered()) {
    _error.ErrAlreadyRegistered();
  }
  _client->setPassword(_token[1]);
}

void RequestHandler::join() {
  printDebug("command", _token[0]);
  // if (no param) re
  sendToClient(_fd, "");
}

void RequestHandler::privmsg() {
  const std::string response =
      "Hello from the server!";  // client connection test
  sendToClient(_fd, response);
}

void RequestHandler::kick() {}

void RequestHandler::invite() {}

void RequestHandler::topic() {}

void RequestHandler::mode() {}

void RequestHandler::pong() {
  if (_token.size() < 2) {
    _error.ErrNeedMoreParams();
  } else if (_token[1].empty()) {
    _error.ErrNoOrigin();
  }
  // _messenger.setPrefix("prefix");
  // _messenger.setCommand("Pong");
}
