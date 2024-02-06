#include "../RequestHandler.hpp"

void RequestHandler::who() {
  std::string member;
  std::string flag;
  if (_token.size() < 2) {
    _msg.ErrUnexpected(_fd);
    return;
  }
  if (_token[1][0] == '#') {
    Channel* channel = Server::_channelNames[_token[1]];
    std::set<std::string>::const_iterator it;
    std::set<std::string> members = channel->getMembers();
    for (it = members.begin(); it != members.end(); it++) {
      if (channel->isOp(*it))
        flag = "H@";
      else
        flag = "H";
      _msg.RplWhoReply(_fd, *it, _token[1], flag);
    }
  }
  _msg.RplEndOfWho(_fd, _token[1]);
}