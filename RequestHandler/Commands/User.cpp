#include "../RequestHandler.hpp"

// USER <username> 0 * <realname>
void RequestHandler::user() {
  if (_token.size() != 5) {
    _msg.ErrNeedMoreParams(_fd, "USER");
    return;
  }
  std::string username = _token[1];
  std::string hostname = _token[3];
  std::string realname = _token[4];
  if (_client->getIsRegistered()) {
    _msg.ErrAlreadyRegistered(_fd);
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
}