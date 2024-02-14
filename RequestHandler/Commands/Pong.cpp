#include "../RequestHandler.hpp"

void RequestHandler::pong() {
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, "PONG");
    return;
  }

  if (_token[1].empty()) {
    _msg.ErrNoOrigin(_fd);
    return;
  }

  _msg.setPrefix(SERVER);
  _msg.setParam("PONG " + SERVER);
  _msg.setTrailing(_token[1]);
  _msg.addRespondToClient(_fd);
}