#include "RequestHandler.hpp"

RequestHandler::RequestHandler(Client* client, const std::string& request,
                               const std::string& password)
    : _fd(client->getFd()),
      _client(client),
      _request(request),
      _password(password) {
  this->_error.setFd(_fd);
  _commandMap["CAP"] = &RequestHandler::cap;
  _commandMap["PASS"] = &RequestHandler::pass;
  _commandMap["NICK"] = &RequestHandler::pass;
  _commandMap["USER"] = &RequestHandler::pass;
  _commandMap["JOIN"] = &RequestHandler::join;
  _commandMap["PRIVMSG"] = &RequestHandler::privmsg;
  _commandMap["PING"] = &RequestHandler::pong;
  // 추후에 명령어 추가될때마다 함수 포인터 추가
}

// 파싱 수정 : param에 공백 들어오는 경우 고려해야 함
void RequestHandler::parse() {
  std::stringstream ss(_request);
  std::string str;
  while (getline(ss, str, ' ')) {
    _token.push_back(str);
  }
  _command = _token[0];
}

void RequestHandler::execute() {
  parse();
  // Find command
  std::map<std::string, RequestHandler::CommandFunction>::iterator found =
      _commandMap.find(_command);
  // 임시
  if (found == _commandMap.end()) {
    // throw err
    return;
  }
  _messenger.setCommand(_command);
  (this->*(found->second))();
}

// Commands

void RequestHandler::sendToClient(int socket, const std::string& msg) {
  const std::string reply = msg + CRLF;
  if (send(socket, &reply, reply.length(), 0) == -1) {
    throw std::runtime_error("Send error");
  }
}

void RequestHandler::cap() {
  // Make reply for...
  if (_token[1] == "LS") {  // CAP LS
    sendToClient(_fd, "CAP * LS :");
  } else if (_token[1] == "END") {  // CAP END
    sendToClient(_fd, "");
  }
}

// prefix
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
    if (pos == std::string::npos) {
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
  if (_token.size() != 5) {
    _error.ErrNeedMoreParams();
  }
  std::string username = _token[1];
  std::map<int, Client*>::iterator iter = Server::_clientFds.begin();
  for (iter; iter != Server::_clientFds.end(); iter++) {
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

  if (!(_client->getPassword().empty() || _client->getNickname().empty() ||
        _client->getUsername().empty())) {
    _client->setIsRegisterd(true);
  } else {
    _error.ErrUnknown();
  }
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
  } else {
    sendToClient(_fd, RPL_WELCOME);
  }
}

void RequestHandler::join() {
  // if (no param) re
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
  _messenger.setPrefix("prefix");
  _messenger.setCommand("Pong");
}
