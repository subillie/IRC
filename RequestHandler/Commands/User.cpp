#include "../RequestHandler.hpp"

// USER <username> 0 * <realname>
void RequestHandler::user() {
  // nickname을 받지 못했을 때
  if (_client->getNickname().empty()) {
    _msg.ErrNotRegistered(_fd);
    throw("Quit");
    return;
  }
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
  // User 정보가 다 있을 경우 인증 확인
  if (!(_client->getUsername().empty())) {
    _client->setIsRegisterd(true);
  } else {
    _msg.ErrNotRegistered(_fd);
    throw("Quit");
    return;
  }
  std::cout << *_client;  // debug
  _msg.RplWelcome(_fd);
  _msg.RplYourHost(_fd);
  _msg.RplCreated(_fd);
  _msg.RplMyinfo(_fd);
  _msg.RplISupport(_fd);
}