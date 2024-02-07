#include "../RequestHandler.hpp"

// PASS <password>
void RequestHandler::pass() {
  // 인자가 없을 때
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, "PASS");
    return;
  }

  // 비번 틀림 ERR_PASSWDMISMATCH => close connection
  if (_token[1] != _password) {
    _msg.ErrPasswdMismatch(_fd);
    return;
  }

  // 이미 가입 됨 ERR_ALREADYREGISTERED
  if (_client->getIsRegistered()) {
    _msg.ErrAlreadyRegistered(_fd);
    return;
  }

  _client->setPassword(_token[1]);
}