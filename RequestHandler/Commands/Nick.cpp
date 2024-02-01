#include "../RequestHandler.hpp"

// NICK <nickname>
void RequestHandler::nick() {
  // 올바른 password를 못받았을 때
  if (_client->getPassword().empty()) {
    _msg.ErrNotRegistered(_fd);
    std::string prefix = _client->getPrefix();
    throw("Quit");
    return;
  }
  if (_token.size() != 2) {
    _msg.ErrNoNickNameGiven(_fd);
    return;
  } else if (Server::_clientNicks.find(_token[1]) !=
             Server::_clientNicks.end()) {
    _msg.ErrNickNameInUse(_fd, _token[1]);
    return;
  } else {
    if (std::isdigit(_token[1][0])) {
      _msg.ErrErroneusNickName(_fd, _token[1]);
      return;
    }
    size_t pos = _token[1].find_first_not_of(
        LOWERCASE + UPPERCASE + SPECIAL_CHAR + DIGIT, 1);
    // 닉네임이 규칙에 맞지 않는 경우
    if (_token[1].length() > 31 || pos != std::string::npos) {
      _msg.ErrErroneusNickName(_fd, _token[1]);
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