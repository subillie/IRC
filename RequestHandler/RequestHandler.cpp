#include "RequestHandler.hpp"

RequestHandler::RequestHandler(Client* client, const std::string& request,
                               const std::string& password)
    : _fd(client->getFd()),
      _client(client),
      _request(request),
      _password(password) {
  this->_error.setFd(_fd);
  _commandMap["CAP"] = &RequestHandler::cap;
  _commandMap["PASS"] = &RequestHandler::pass;
  _commandMap["NICK"] = &RequestHandler::nick;
  _commandMap["USER"] = &RequestHandler::user;
  _commandMap["JOIN"] = &RequestHandler::join;
  _commandMap["PRIVMSG"] = &RequestHandler::privmsg;
  _commandMap["PING"] = &RequestHandler::pong;
  // 추후에 명령어 추가될때마다 함수 포인터 추가
}

// 파싱 수정 : param에 공백 들어오는 경우 고려해야 함
void RequestHandler::parse() {
  printDebug("req", _request);
  std::stringstream ss(_request);
  std::string str;
  while (getline(ss, str, ' ')) {
    printCyan(str);
    _token.push_back(str);
  }
  _command = _token[0];
}

void RequestHandler::execute() {
  parse();
  // Find command
  std::map<std::string, RequestHandler::CommandFunction>::iterator found =
      _commandMap.find(_command);
  // 임시
  if (found == _commandMap.end()) {
    printRed(_token[0]);
    // throw err
    return;
  }
  //_messenger.setCommand(_command);
  (this->*(found->second))();
}

void RequestHandler::sendToClient(int socket, const std::string& msg) {
  const std::string reply = msg + CRLF;
  if (send(socket, &reply, reply.length(), 0) == -1) {
    throw std::runtime_error("Send error");
  }
}
