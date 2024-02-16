#include "../RequestHandler.hpp"

// NICK <nickname>
void RequestHandler::nick() {
  // 올바른 password를 못 받았을 때
  if (_client->getPassword().empty()) {
    _msg.ErrNotRegistered(_fd);
    return;
  }

  // 인자가 없을 때
  if (_token.size() != 2 || _token[1].empty()) {
    _msg.ErrNoNickNameGiven(_fd);
    return;
  }

  const std::string& newNick = _token[1];
  const std::string oldNick = _client->getNickname();

  // 변경하려는 닉네임이 이전과 같은 경우
  if (oldNick == newNick) return;

  // 중복되는 닉네임이 있는 경우
  if (isExistingClient(newNick)) {
    _msg.ErrNickNameInUse(_fd, newNick);
    return;
  }

  // 닉네임이 규칙에 맞지 않는 경우
  if (std::isdigit(newNick[0])) {
    _msg.ErrErroneusNickName(_fd, newNick);
    return;
  }
  size_t pos = newNick.find_first_not_of(
      LOWERCASE + UPPERCASE + SPECIAL_CHAR + DIGIT, 1);
  if (newNick.length() > 31 || pos != std::string::npos) {
    _msg.ErrErroneusNickName(_fd, newNick);
    return;
  }

  if (_client->getIsRegistered()) {
    // Reply를 보낼 client 명단 만듦
    std::set<std::string> clientsToReply;
    std::set<std::string> channels = _client->getChannels();
    std::set<std::string>::iterator chanIter, memIter;
    for (chanIter = channels.begin(); chanIter != channels.end(); chanIter++) {
      std::set<std::string> members =
          Server::_channelNames[*chanIter]->getMembers();
      for (memIter = members.begin(); memIter != members.end(); memIter++) {
        clientsToReply.insert(*memIter);
      }
    }

    // : two!root@127.0.0.1 NICK :new
    // 명단에 있는 모든 client에게 reply를 보냄
    for (memIter = clientsToReply.begin(); memIter != clientsToReply.end();
         memIter++) {
      _msg.setPrefix(_client->getPrefix());
      _msg.setParam("NICK");
      _msg.setTrailing(newNick);
      _msg.addReplyToClient(Server::_clientNicks[*memIter]->getFd());
    }

    // Nickname 변경
    _client->setNickname(newNick);
    Server::_clientNicks.erase(oldNick);
    Server::_clientNicks[newNick] = _client;

    // 가입한 모든 channel 정보 수정
    for (chanIter = channels.begin(); chanIter != channels.end(); chanIter++) {
      Channel* channel = Server::_channelNames[*chanIter];
      if (channel->isOp(oldNick)) {
        channel->removeOp(oldNick);
        channel->addOp(newNick);
      }
      if (channel->isInvitee(oldNick)) {
        channel->removeInvitee(oldNick);
        channel->addInvitee(newNick);
      }
      channel->removeMember(oldNick);
      channel->addMember(newNick);
    }
  } else {
    // 등록 전 닉네임 변경하려는 경우
    if (oldNick != "*") Server::_clientNicks.erase(oldNick);
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