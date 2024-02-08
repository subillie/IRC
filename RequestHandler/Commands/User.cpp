#include "../RequestHandler.hpp"

// USER <username> 0 * <realname>
void RequestHandler::user() {
  // 이미 등록이 되어있을 때
  if (_client->getIsRegistered()) {
    _msg.ErrAlreadyRegistered(_fd);
    return;
  }

  // nickname을 받지 못했을 때
  if (_client->getNickname() == "*") {
    _msg.ErrNotRegistered(_fd);
    return;
  }

  if (_token.size() != 5) {
    _msg.ErrNeedMoreParams(_fd, "USER");
    return;
  }
  std::string username = _token[1];
  std::string hostname = _token[3];
  std::string realname = _token[4];
  if (_client->getIsRegistered()) {
    return;
  }

  bool isOutOfLen = (username.length() < 1 || username.length() > 12);
  bool isSpecialChar = (username.find_first_not_of("\0@") == std::string::npos);
  if (isOutOfLen || isSpecialChar) {
    _msg.ErrUnexpected();
    return;
  }

  _client->setUsername(username);
  _client->setHostname(hostname);
  _client->setRealname(realname);
  // User 정보가 다 있을 경우 인증 확인
  if (!(_client->getUsername().empty())) {
    _client->setIsRegisterd(true);
  } else {
    _msg.ErrNotRegistered(_fd);
    throw("Client cannot register to server");
    return;
  }
  std::cout << *_client;  // Debug
  _msg.RplWelcome(_fd);
  _msg.RplYourHost(_fd);
  _msg.RplCreated(_fd);
  _msg.RplMyinfo(_fd);
  _msg.RplISupport(_fd);
}