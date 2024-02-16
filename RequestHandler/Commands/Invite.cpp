#include "../RequestHandler.hpp"

// /invite <nickname> <channel>
void RequestHandler::invite() {
  // 인자가 2개가 아닐 때
  if (_token.size() < 3) {
    _msg.ErrNeedMoreParams(_fd, _token[0]);
    return;
  }
  std::string invitee = _token[1];
  std::string channel = _token[2];
  if (channel[0] != '#') {
    _msg.ErrBadChanMask(_fd);
  }

  // 초대하려는 유저가 존재하지 않을 때
  if (Server::_clientNicks.find(invitee) == Server::_clientNicks.end()) {
    _msg.ErrNoSuchNick(_fd, invitee);
    return;
  }

  // 채널이 존재하지 않을 때 (= 채널에 아무도 없을 때)
  if (Server::_channelNames.find(channel) == Server::_channelNames.end()) {
    _msg.ErrNoSuchChannel(_fd, channel);
    return;
  }

  // 초대하는 유저가 채널의 멤버가 아닐 때
  Channel *chanToInvite = Server::_channelNames[channel];
  if (!chanToInvite->isMember(_client->getNickname())) {
    _msg.ErrNotOnChannel(_fd, channel);
    return;
  }

  // 채널이 Invite Only이고 유저가 채널의 Operator가 아닐 때
  if (chanToInvite->isMode(INVITE_ONLY_CHANNEL) &&
      !chanToInvite->isOp(_client->getNickname())) {
    _msg.ErrChanOPrivsNeeded(_fd, channel);
    return;
  }

  // 초대하려는 유저가 이미 채널에 있을 때
  if (chanToInvite->isMember(invitee)) {
    _msg.ErrUserOnChannel(_fd, invitee, channel);
    return;
  }

  // RPL 및 invitee에게 초대장 전송 (dan-!d@localhost INVITE Wiz #test)
  _msg.RplInviting(_fd, invitee, channel);
  chanToInvite->addInvitee(invitee);
  int fdToInvite = Server::_clientNicks[invitee]->getFd();
  _msg.setPrefix(_client->getPrefix());
  _msg.setParam("INVITE " + invitee + " " + channel);
  _msg.addReplyToClient(fdToInvite);
}