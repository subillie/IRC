#include "../RequestHandler.hpp"

// k 는 항상 인자 존재 (그런데 지울 땐 없어도 되는듯..???)
// l은 set할 때만 인자 존재
// i, t는 항상 인자 없음
// para가 있어야하는데 없으면 ERR_INVALIDMODEPARAM
bool RequestHandler::addModeToChannel(Channel* channel, const char& mode) {
  switch (mode) {
    // MODE +l <number>
    case CLIENT_LIMIT_CHANNEL:
      // 인자가 없으면
      if (_token.size() < 4) {
        _msg.setTrailing("You must specify a parameter for mode l");
        _msg.ErrInvalidModeParam(_fd, channel->getName(), mode);
        return false;
      }
      // MODE #hi +l :10
      size_t limit = atoi(_token[3].c_str());
      if (limit < 1) {
        _msg.setTrailing("Invalid parameter for mode l");
        _msg.ErrInvalidModeParam(_fd, channel->getName(), mode);
        return false;
      }
      _msg.setParam(_msg.getParam() + "+l");
      _msg.setTrailing(_token[3]);
      break;
    case INVITE_ONLY_CHANNEL:
      break;
    case PROTECTED_TOPIC:
      break;
    case KEY_CHANNEL:
      break;
    case 'o':
      break;
    default:
      _msg.ErrUModeUnknownFlag(_fd);
      return false;
  }
  return true;
}

bool RequestHandler::removeModeFromChannel(Channel* channel, const char& mode) {
  switch (mode) {
      // MODE #hi :-l
      // two!root@127.0.0.1 MODE #hi :-l
    case CLIENT_LIMIT_CHANNEL:
      _msg.setTrailing("-l");
      break;
    case INVITE_ONLY_CHANNEL:
      break;
    case PROTECTED_TOPIC:
      break;
    case KEY_CHANNEL:
      break;
    case 'o':
      break;
    default:
      _msg.ErrUModeUnknownFlag(_fd);
      return false;
  }
  return true;
}

void RequestHandler::channelMode(const std::string& target) {
  const std::string& nick = _client->getNickname();
  const std::string& username = _client->getUsername();
  const std::string& hostname = _client->getHostname();

  if (Server::_channelNames.find(target) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, target);
    return;
  }
  Channel* channel = Server::_channelNames[target];
  // <modestring> 이 없으면
  if (_token.size() < 3) {
    _msg.RplChannelModeIS(_fd, target);
    return;
  }
  std::set<std::string> channelOps = channel->getOps();
  // operator가 아니면
  if (channelOps.find(nick) == channelOps.end()) {
    _msg.ErrChanOPrivsNeeded(_fd, target);
    return;
  }
  // std::string param = "MODE " + target;
  const std::string& modestring = _token[2];
  // i, t, k, l, o 외엔 모두 에러
  if (modestring.length() > 2 ||
      modestring.find_first_not_of(AVAILABLE_CHAN_MODES + "o", 1) !=
          std::string::npos) {
    _msg.ErrUnknownMode(_fd, modestring);
    return;
  }
  // <nickname>!<username>@<hostname>
  _msg.setPrefix(nick + "!" + username + "@" + hostname);
  //  MODE <channel>
  _msg.setParam("MODE " + target + " ");
  if (modestring[0] == '+') {
    if (!addModeToChannel(channel, modestring[1])) return;
  } else if ((modestring[0]) == '-') {
    if (!removeModeFromChannel(channel, modestring[1])) return;
  }
  // 채널 모든 멤버에게 MODE 전송 -> channel에 sendToAll 구현하기
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
    return;
  }
  // <modestring> 지원하지 않는 모드는 에러 (일단 +i 외에는 다 에러)
  if (_token[2].length() > 1 &&
      AVAILABLE_USER_MODES.find(_token[2][1]) != std::string::npos) {
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
