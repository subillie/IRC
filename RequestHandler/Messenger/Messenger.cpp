#include "Messenger.hpp"

Messenger::Messenger() : _prefix(""), _param(""), _trailing("") {
  FD_ZERO(&_writeSet);
}

void Messenger::setPrefix(const std::string& prefix) { _prefix = prefix; }

void Messenger::setParam(const std::string& param) { _param = param; }

void Messenger::setTrailing(const std::string& trailing) {
  _trailing = trailing;
}

void Messenger::addReplyToClient(int fd) {
  Client* client = Server::_clientFds[fd];
  if (!_prefix.empty()) _prefix = ":" + _prefix + " ";
  if (!_trailing.empty()) _trailing = " :" + _trailing;
  std::string response = _prefix + _param + _trailing + CRLF;
  printCyan(response);
  client->addReplies(response);
  // client[fd]->request <- response
  //   if (send(fd, response.c_str(), response.length(), 0) == -1) {
  //     throw fd;
  //   }
  addWriteSet(fd);
  _prefix.clear();
  _param.clear();
  _trailing.clear();
}

void Messenger::addReplyToChannel(Channel* channel) {
  std::set<std::string> members = channel->getMembers();
  std::string prefix = _prefix;
  std::string param = _param;
  std::string trailing = _trailing;
  for (std::set<std::string>::const_iterator it = members.begin();
       it != members.end(); it++) {
    _prefix = prefix;
    _param = param;
    _trailing = trailing;
    addReplyToClient(Server::_clientNicks[*it]->getFd());
  }
}

const std::string& Messenger::getPrefix() const { return _prefix; }

const std::string& Messenger::getParam() const { return _param; }

const std::string& Messenger::getTrailing() const { return _trailing; }

const fd_set& Messenger::getWriteSet() const { return _writeSet; }

void Messenger::addWriteSet(int fd) {
  if (!FD_ISSET(fd, &_writeSet)) FD_SET(fd, &_writeSet);
}
