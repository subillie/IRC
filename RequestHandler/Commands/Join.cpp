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
    std::cout << "channel: " << channel << " (" << channel.length()
              << "), password: " << password << std::endl;  // TODO: debug
  }

  std::map<std::string, std::string>::iterator iter = keys.begin();
  for (; iter != keys.end(); iter++) {
    // 채널명이 유효하지 않을 때
    if (iter->first.empty() || iter->first[0] != '#' ||
        iter->first.find(SPECIAL_CHAR) != std::string::npos) {
      _msg.ErrBadChanMask(_fd);
      continue;
    }
    // 비밀번호가 유효하지 않을 때
    if (iter->second.find(SPECIAL_CHAR) != std::string::npos) {
      _msg.ErrUnexpected(_fd);
      continue;
    }
    // 채널이 없으면 생성
    if (Server::_channelNames.find(iter->first) ==
        Server::_channelNames.end()) {
      Server::_channelNames[iter->first] =
          new Channel(PROTECTED_TOPIC, iter->first);
    } else {
      Channel* chanToJoin = Server::_channelNames[iter->first];
      std::list<std::string> memberList = chanToJoin->getMembers();
      std::list<std::string>::iterator membIter =
          std::find(memberList.begin(), memberList.end(), iter->first);
      // 이미 참가 중인 채널이면 무시
      if (membIter != memberList.end()) {
        continue;
        // 채널이 존재하고 멤버 명단에 없으면 참가
      } else {
        std::list<char> modeList = chanToJoin->getModes();
        // 해당 채널이 Key Channel Mode이면 비밀번호 확인
        if (std::find(modeList.begin(), modeList.end(), KEY_CHANNEL) !=
            modeList.end()) {
          if (chanToJoin->getPassword() != iter->second) {
            _msg.ErrBadChannelKey(_fd, iter->first);
            continue;
          }
          // 해당 채널이 Invite Only Channel Mode이면 초대 리스트에 있는지 확인
        } else if (std::find(modeList.begin(), modeList.end(),
                             INVITE_ONLY_CHANNEL) != modeList.end()) {
          std::list<std::string> inviteeList = chanToJoin->getInvitees();
          if (std::find(inviteeList.begin(), inviteeList.end(),
                        _client->getNickname()) ==
              chanToJoin->getInvitees().end()) {
            _msg.ErrInviteOnlyChan(_fd, iter->first);
            continue;
          }
          // 해당 채널이 Client Limit Channel Mode이면 인원 제한 확인
        } else if (std::find(modeList.begin(), modeList.end(),
                             CLIENT_LIMIT_CHANNEL) != modeList.end()) {
          if (chanToJoin->getLimit() < chanToJoin->getMembers().size()) {
            _msg.ErrTooManyChannels(_fd);
            continue;
          }
        }
        // 채널에 유저 추가
        chanToJoin->addMember(iter->first);
        // 해당 채널에 topic이 존재한다면 topic 전송
        if (!chanToJoin->getTopic().empty()) {
          _msg.RplTopic(_fd, iter->first, chanToJoin->getTopic());
        }
        // 해당 채널의 모든 유저에게 join 메시지 전송
        for (membIter = memberList.begin(); membIter != memberList.end();
             membIter++) {
          _msg.RplNamReply(_fd, iter->first, *membIter);
          _msg.RplEndOfNames(_fd, iter->first);
        }
      }
    }
  }

  _msg.sendToClient(_fd);
}