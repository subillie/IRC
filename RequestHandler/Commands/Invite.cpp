#include "../RequestHandler.hpp"

// /invite <nickname> <channel>
void RequestHandler::invite() {
  // 인자가 2개가 아닐 때
  if (_token.size() < 3) {
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }
  // 채널이 존재하지 않을 때
}