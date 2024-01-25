#include "RequestHandler.hpp"

RequestHandler::RequestHandler(Client* client, const std::string& request,
                               const std::string& password)
    : _client(client), _request(request), _password(password) {
  this->_error.setFd(_client->getFd());
  _commandMap["CAP"] = &RequestHandler::cap;
  _commandMap["PASS"] = &RequestHandler::pass;
  _commandMap["NICK"] = &RequestHandler::pass;
  _commandMap["USER"] = &RequestHandler::pass;
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
  // 임시
  if (found == _commandMap.end()) {
    // throw err
    return;
  }
  (this->*(found->second))();
}

// Commands

void sendToClient(int socket, const std::string& msg) {
  std::string reply = msg + "\r\n";
  if (send(socket, reply.c_str(), reply.size(), 0) == -1) {
    perror("send: ");  // throw ??
  }
}

void RequestHandler::cap() {
  // Make reply for...
  std::string reply;
  if (_token[1] == "LS") {  // CAP LS
    reply = "CAP * LS :";
  } else if (_token[1] == "END") {  // CAP END
    reply = "";
  }
  sendToClient(_client->getFd(), reply);
}

// prefix
void RequestHandler::nick() {
  // 닉네임 규칙 확인
  // 닉네임 중복 체크

  // 이미 닉네임이 있어도 수정되도록
}

void RequestHandler::user() {}

// PASS <password>
void RequestHandler::pass() {
  if (_token.size() != 2) {
    // 인자 1개ERR_NEEDMOREPARAMS
  } else if (_client->getIsAuthenticated()) {
    // 이미 가입 됨 ERR_ALREADYREGISTERED
  } else if (_token[1] != _password) {
    // 비번 틀림 ERR_PASSWDMISMATCH => close connection
  }
  // 가입 여부 확인 -> 가입 전까지는 pass 여러 번 받을 수 있음, 마지막꺼만
  // 유효함, 등록되면 변경 불가 server pass 일치 여부 확인
  // 일치하지 않으면 passdmismatch
  //
  // sendresponse
}

void RequestHandler::join() {
  // if (no param) re
}

void RequestHandler::privmsg() {
  const char* response = "Hello from the server!";  // client connection test
  if (send(_client->getFd(), response, strlen(response), 0) == -1) {
    throw std::runtime_error("Send error");
  }
}

void RequestHandler::kick() {}

void RequestHandler::invite() {}

void RequestHandler::topic() {}

void RequestHandler::mode() {}
