#include "RequestHandler.hpp"

void RequestHandler::init() {
  _commandMap["JOIN"] = &RequestHandler::join;
  _commandMap["PRIVMSG"] = &RequestHandler::privmsg;
}

RequestHandler::RequestHandler(int clientFd, std::string request) {
  init();
  // parse(request); => 토큰 저장
}
void RequestHandler::execute() {
  // find command
  std::map<std::string, RequestHandler::CommandFunction>::iterator found =
      _commandMap.find(_token[0]);
  if (found == _commandMap.end()) {
    // send unknown command error to client
    return;
  }
  (this->*(found->second))(_clientFd, _token);
}

// commands
void RequestHandler::join(int fd, std::vector<std::string> token) {}
void RequestHandler::privmsg(int fd, std::vector<std::string> token) {}
