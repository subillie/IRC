#include "../RequestHandler.hpp"

void RequestHandler::channelMode(const std::string& target) {
  //   const std::string& nick = _client->getNickname();
  //   const std::string& username = _client->getUsername();
  //   const std::string& hostname = _client->getHostname();
  if (Server::_channelNames.find(target) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, target);
  }
}

void RequestHandler::userMode(const std::string& target) {
  const std::string& nick = _client->getNickname();
  const std::string& username = _client->getUsername();
  const std::string& hostname = _client->getHostname();
  // 존재하지 않는 닉네임이면
  if (Server::_clientNicks.find(target) == Server::_clientNicks.end()) {
    _msg.ErrNoSuchNick(_fd, target);
    return;
  }
  // 명령어를 보낸 유저와 닉네임이 다르면
  if (target != _client->getNickname()) {
    _msg.ErrUsersDontMatch(_fd);
    return;
  }
  // <modestring> 이 없으면
  if (_token.size() == 2) {
    _msg.RplUModeIs(_fd, _client->getMode());
  }
  // <modestring> 지원하지 않는 모드는 에러 (일단 +i 외에는 다 에러)
  if (_token[2] == "+i") {
    _msg.setPrefix(nick + "!" + username + "@" + hostname);
    _msg.setParam("MODE " + nick);
    _msg.setTrailing(_token[2]);
    _msg.sendToClient(_fd);
    _client->setMode(_token[2]);
  } else {
    _msg.ErrUModeUnknownFlag(_fd);
  }
}

// MODE <target> [<modestring> [<mode arguments>...]]
void RequestHandler::mode() {
  if (_token.size() < 2) {
    _msg.ErrUnexpected(_fd);
    return;  // 이런 경우는 없을 것 같긴 하지만 일단 예외처리
  }

  // 채널모드인지 유저모드인지 확인
  _token[1][0] == '#' ? channelMode(_token[1]) : userMode(_token[1]);
}
