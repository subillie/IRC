#include "../RequestHandler.hpp"

// /invite <nickname> <channel>
void RequestHandler::invite() {
  // 인자가 2개가 아닐 때
  if (_token.size() < 3) {
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }
  std::string nickname = _token[1];
  std::string channel = _token[2];

  // 채널이 존재하지 않거나 채널에 유저가 한 명도 없을 때
  if (Server::_channelNames.find(channel) == Server::_channelNames.end() ||
      Server::_channelNames[channel]->getMembers().empty()) {
    _msg.ErrNoSuchChannel(_fd, channel);
    return;
  }

  // 초대하려는 유저가 채널의 멤버가 아닐 때
  Channel *chanToInvite = Server::_channelNames[channel];
  std::list<std::string> membList = chanToInvite->getMembers();
  if (std::find(membList.begin(), membList.end(), nickname) == membList.end()) {
    _msg.ErrNotOnChannel(_fd, channel);
    return;
  }

  // 채널이 Invite Only이고 유저가 채널의 Operator가 아닐 때
  std::list<char> modeList = chanToInvite->getModes();
  std::list<std::string> operList = chanToInvite->getOperators();
  if (std::find(modeList.begin(), modeList.end(), INVITE_ONLY) !=
          modeList.end() &&
      std::find(operList.begin(), operList.end(), nickname) == operList.end()) {
    _msg.ErrChanOPrivsNeeded(_fd, channel);
    return;
  }
<<<<<<< HEAD

  // 초대하려는 유저가 이미 채널에 있을 때
  if (std::find(membList.begin(), membList.end(), nickname) != membList.end()) {
    _msg.ErrUserOnChannel(_fd, nickname, channel);
    return;
  }

  // 유저에게 초대장 전송
  chanToInvite->addInvitee(nickname);
  int fdToInvite = Server::_clientNicks[nickname]->getFd();
  _msg.RplInviting(fdToInvite, nickname, channel);
=======
>>>>>>> d897747 (feat: error handling 중)
}