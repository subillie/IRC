#include "RequestHandler.hpp"

RequestHandler::RequestHandler(int clientFd, const std::string& request)
    : _clientFd(clientFd) {
  size_t found = request.find("\r\n");  // CRLF
  _request = request.substr(0, found);
  _commandMap["JOIN"] = &RequestHandler::join;
  _commandMap["PRIVMSG"] = &RequestHandler::privmsg;
  // 추후에 명령어 추가될때마다 함수 포인터 추가
}

void RequestHandler::parse() {
  std::stringstream ss(_request);
  std::string str;
  while (getline(ss, str, ' ')) {
    _token.push_back(str);
  }
  _command = _token[0][0] == ':' ? _token[1] : _token[0];
}

void RequestHandler::execute() {
  parse();
  // Find command
  std::map<std::string, RequestHandler::CommandFunction>::iterator found =
      _commandMap.find(_command);
  if (found == _commandMap.end()) {
    // throw err
    return;
  }
  (this->*(found->second))(_clientFd, _token);
}

// Commands
void RequestHandler::join(int fd, std::vector<std::string> token) {
  (void)fd;
  (void)token;
}

void RequestHandler::privmsg(int fd, std::vector<std::string> token) {
  (void)fd;
  (void)token;
  const char* response = "Hello from the server!";  // client connection test
  if (send(_clientFd, response, strlen(response), 0) == -1) {
    perror("send: ");
  }
}
