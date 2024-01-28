#include "RequestHandler.hpp"

RequestHandler::RequestHandler(Client* client, const std::string& request,
                               const std::string& password)
    : _fd(client->getFd()),
      _client(client),
      _request(request),
      _password(password) {
  _commandMap["CAP"] = &RequestHandler::cap;
  _commandMap["PASS"] = &RequestHandler::pass;
  _commandMap["NICK"] = &RequestHandler::nick;
  _commandMap["USER"] = &RequestHandler::user;
  _commandMap["JOIN"] = &RequestHandler::join;
  _commandMap["PRIVMSG"] = &RequestHandler::privmsg;
  _commandMap["PING"] = &RequestHandler::pong;
  // 추후에 명령어 추가될때마다 함수 포인터 추가
}

// TODO : 대격변 (다 이상함)
void RequestHandler::parse() {
  std::cout << _request << std::endl;
  std::stringstream ss(_request);
  std::string str;
  while (getline(ss, str, ' ')) {
    if (str.find(":") != std::string::npos) {
      str.erase(0, 1);
      std::string remainer;
      getline(ss, remainer);
      _token.push_back(str + " " + remainer);
      break;
    }
    _token.push_back(str);
  }
  _command = _token[0];
}

void RequestHandler::execute() {
  Messenger msg;
  parse();
  std::map<std::string, RequestHandler::CommandFunction>::iterator found =
      _commandMap.find(_command);
  if (found == _commandMap.end()) {
    msg.ErrUnknownCommand(_fd);
    return;
  }
  (this->*(found->second))();
}
