#include "../RequestHandler.hpp"

// NICK <nickname>
void RequestHandler::nick() {
  // 올바른 password를 못받았을 때
  if (_client->getPassword().empty()) {
    _msg.ErrNotRegistered(_fd);
    std::string prefix = _client->getPrefix();
    throw("Quit");
    return;
  }
  // 인자가 없을 때
  if (_token.size() != 2 || _token[1].empty()) {
    _msg.ErrNoNickNameGiven(_fd);
    return;
  }
  const std::string& newNick = _token[1];
  const std::string& oldNick = _client->getNickname();
  if (isExistingClient(newNick)) {
    _msg.ErrNickNameInUse(_fd, newNick);
    return;
  }
  if (std::isdigit(newNick[0])) {
    _msg.ErrErroneusNickName(_fd, newNick);
    return;
  }
  size_t pos = newNick.find_first_not_of(
      LOWERCASE + UPPERCASE + SPECIAL_CHAR + DIGIT, 1);
  // 닉네임이 규칙에 맞지 않는 경우
  if (newNick.length() > 31 || pos != std::string::npos) {
    _msg.ErrErroneusNickName(_fd, newNick);
    return;
  }

  // nickname 설정이 되어 있을 경우
  if (!oldNick.empty()) {
    Server::_clientNicks.erase(oldNick);
    Server::_clientNicks[newNick] = _client;
    // : two!root@127.0.0.1 NICK :new
    _msg.setPrefix(_client->getPrefix());
    _msg.setParam("NICK");
    _msg.setTrailing(newNick);
    // 닉네임 변경 시 모든 클라이언트에 메시지 보냄
    Server::sendToAllClients(_msg);
    _client->setNickname(newNick);
  } else {
    _client->setNickname(newNick);
    Server::_clientNicks[newNick] = _client;
  }
}

// 대소문자 구분 없이 중복일 경우 확인
bool RequestHandler::isExistingClient(const std::string& client) {
  std::map<std::string, Client*>::iterator it;
  for (it = Server::_clientNicks.begin(); it != Server::_clientNicks.end();
       it++) {
    std::string existingClient = it->second->getNickname();
    if (client.length() != existingClient.length()) continue;
    for (size_t i = 0; i <= client.length(); i++) {
      if (i == client.length()) return true;
      if (tolower(client[i]) != tolower(existingClient[i])) break;
    }
  }
  return false;
}