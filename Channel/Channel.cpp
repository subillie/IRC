#include "Channel.hpp"

Channel::Channel(const char& mode, const std::string& name)
    : _limit(0), _name(name) {
  _modes.push_back(mode);
}

void Channel::addMode(const char mode) { _modes.push_back(mode); }

void Channel::addOp(const std::string& op) { _ops.push_back(op); }

void Channel::addMember(const std::string& member) {
  _members.push_back(member);
}

void Channel::addInvitee(const std::string& member) {
  _invitees.push_back(member);
}

void Channel::removeOp(const std::string& op) { _ops.remove(op); }

void Channel::removeMember(const std::string& member) {
  _members.remove(member);
}

void Channel::removeInvitee(const std::string& member) {
  _invitees.remove(member);
}

void Channel::setLimit(size_t limit) { _limit = limit; }

void Channel::setName(const std::string& name) { _name = name; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

void Channel::setPassword(const std::string& password) { _password = password; }

size_t Channel::getLimit() const { return _limit; }

const std::string& Channel::getName() const { return _name; }

const std::string& Channel::getTopic() const { return _topic; }

const std::string& Channel::getPassword() const { return _password; }

const std::list<char>& Channel::getModes() const { return _modes; }

const std::list<std::string>& Channel::getOps() const { return _ops; }

const std::list<std::string>& Channel::getMembers() const { return _members; }

const std::list<std::string>& Channel::getInvitees() const { return _invitees; }