#include "../RequestHandler.hpp"

// /join <channel>{,<channel>} [<key>{,<key>}]
void RequestHandler::join() {
  // 인자가 없을 때
  if (_token.size() < 2) {
    _msg.ErrNeedMoreParams(_fd, "JOIN");
    return;
  }
  if (_token[1] == " ") {
    return;
  }

  std::stringstream ss1(_token[1]), ss2(_token[2]);
  std::string channel, password;
  std::map<std::string, std::string> keys;
  while (std::getline(ss1, channel, ',')) {
    std::getline(ss2, password, ',');
    keys[channel] = password;
  }

  std::map<std::string, std::string>::iterator iter = keys.begin();
  for (; iter != keys.end(); iter++) {
    const std::string& channelName = iter->first;
    const std::string& channelKey = iter->second;

    // 채널명이 유효하지 않을 때
    if (channelName.empty() || channelName[0] != '#' ||
        channelName.length() > MAX_CHANNEL_LEN) {
      _msg.ErrNoSuchChannel(_fd, channelName);
      continue;
    }

    // 이미 가입한 채널 수가 최대치일 때
    if (_client->isMaxJoined()) {
      _msg.ErrTooManyChannels(_fd, channelName);
      break;
    }

    // 채널이 없으면 생성
    if (Server::_channelNames.find(channelName) ==
        Server::_channelNames.end()) {
      printGreen("join: " + channelName + " created\n");
      Server::_channelNames[channelName] =
          new Channel(PROTECTED_TOPIC, channelName);
      addUser(Server::_channelNames[channelName]);
      Server::_channelNames[channelName]->addOp(_client->getNickname());
    } else {
      printGreen("join: " + channelName + " already exists\n");
      Channel* chanToJoin = Server::_channelNames[channelName];
      std::set<std::string> memberList = chanToJoin->getMembers();
      std::set<std::string>::iterator membIter =
          std::find(memberList.begin(), memberList.end(), channelName);
      // 이미 참가 중인 채널이면 무시
      if (membIter != memberList.end()) {
        continue;
        // 채널이 존재하고 멤버 명단에 없으면 참가
      } else {
        std::set<char> modeList = chanToJoin->getModes();
        // 해당 채널이 Key Channel Mode이면 비밀번호 확인
        if (modeList.find(KEY_CHANNEL) != modeList.end()) {
          if (chanToJoin->getPassword() != channelKey) {
            _msg.ErrBadChannelKey(_fd, channelName);
            continue;
          }
          // 해당 채널이 Invite Only Channel Mode이면 초대 리스트에 있는지 확인
        } else if (modeList.find(INVITE_ONLY_CHANNEL) != modeList.end()) {
          std::set<std::string> inviteeList = chanToJoin->getInvitees();
          if (std::find(inviteeList.begin(), inviteeList.end(),
                        _client->getNickname()) ==
              chanToJoin->getInvitees().end()) {
            _msg.ErrInviteOnlyChan(_fd, channelName);
            continue;
          }
          // 해당 채널이 Client Limit Channel Mode이면 인원 제한 확인
        } else if (modeList.find(CLIENT_LIMIT_CHANNEL) != modeList.end()) {
          if (chanToJoin->isFull()) {
            _msg.ErrChannelIsFull(_fd, channelName);
            continue;
          }
        }
        // 채널에 유저 추가
        addUser(chanToJoin);
      }
    }
  }

  // std::map<std::string, Channel*>::iterator it =
  // Server::_channelNames.begin(); for (; it != Server::_channelNames.end();
  // it++) {
  //   std::cout << "channel: " << it->first << std::endl;
  //   std::cout << "members: ";
  //   std::set<std::string> members = it->second->getMembers();
  //   std::set<std::string>::iterator mIter = members.begin();
  //   for (; mIter != members.end(); mIter++) {
  //     std::cout << *mIter << " ";
  //   }
  //   std::cout << std::endl;
  // }

  _msg.sendToClient(_fd);
}

void RequestHandler::addUser(Channel* chanToJoin) {
  // 채널의 멤버 목록에 유저 추가, 클라이언트의 채널 목록에 채널 추가
  std::string nickname = _client->getNickname();
  std::string channelName = chanToJoin->getName();
  chanToJoin->addMember(nickname);
  _client->addChannel(channelName);

  // 해당 채널에 topic이 존재한다면 topic 전송
  if (!chanToJoin->getTopic().empty()) {
    _msg.RplTopic(_fd, channelName, chanToJoin->getTopic());
  }

  // 해당 채널의 모든 유저에게 join 메시지 전송
  std::set<std::string> memberList = chanToJoin->getMembers();
  std::set<std::string>::iterator membIter;
  for (membIter = memberList.begin(); membIter != memberList.end();
       membIter++) {
    _msg.RplNamReply(_fd, nickname, *membIter);
    _msg.RplEndOfNames(_fd, nickname);
  }
}
