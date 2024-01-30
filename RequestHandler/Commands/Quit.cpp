#include "../RequestHandler.hpp"

// /quit [<reason>]
void RequestHandler::quit() {
  std::string reason = "";
  if (_token.size() == 1) {
    reason = "leaving";
  } else {
    for (size_t i = 1; i < _token.size(); i++) {
      reason += _token[i];
      if (i != _token.size() - 1) {
        reason += " ";
      }
    }
  }

  _msg.setParam("QUIT");
  _msg.setTrailing(reason);
  _msg.Error(_fd, reason);

  Server::_clientFds.erase(_fd);
  if (close(_fd) < 0) {
    throw std::runtime_error("Close error");
  }
  Server::_clientNicks.erase(_client->getNickname());
  delete _client;

  // TODO: FD_CLR해야 함 (Server.cpp의 deleteChlient 함수)
}