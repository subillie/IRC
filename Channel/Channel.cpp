#include "Channel.hpp"

#include "../RequestHandler/Messenger/Messenger.hpp"

Channel::Channel(const char& mode, const std::string& name)
    : _limit(0), _name(name) {
  time_t now;
  time(&now);
  _creationTime = ctime(&now);
  _modes.insert(mode);
}

void Channel::addMode(const char mode) { _modes.insert(mode); }

void Channel::addOp(const std::string& op) { _ops.insert(op); }

void Channel::addMember(const std::string& member) { _members.insert(member); }

void Channel::addInvitee(const std::string& member) {
  _invitees.insert(member);
}

void Channel::removeOp(const std::string& op) { _ops.erase(op); }

void Channel::removeMember(const std::string& member) {
  _members.erase(member);
}

void Channel::removeInvitee(const std::string& member) {
  _invitees.erase(member);
}

void Channel::setLimit(size_t limit) { _limit = limit; }

void Channel::setName(const std::string& name) { _name = name; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

void Channel::setPassword(const std::string& password) { _password = password; }

size_t Channel::getLimit() const { return _limit; }

const std::string& Channel::getName() const { return _name; }

const std::string& Channel::getTopic() const { return _topic; }

const std::string& Channel::getPassword() const { return _password; }

const std::string& Channel::getCreationTime() const { return _creationTime; }

const std::set<char>& Channel::getModes() const { return _modes; }

const std::set<std::string>& Channel::getOps() const { return _ops; }

const std::set<std::string>& Channel::getMembers() const { return _members; }

const std::set<std::string>& Channel::getInvitees() const { return _invitees; }

void Channel::sendToAll(Messenger& msg) const {
  for (std::set<std::string>::const_iterator it = _members.begin();
       it != _members.end(); it++) {
    Messenger copy = msg;
    copy.sendToClient(Server::_clientNicks[*it]->getFd());
  }
}