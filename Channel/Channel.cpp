#include "Channel.hpp"

Channel::Channel(const char mode, const std::string& name)
    : _mode(mode), _limit(0), _name(name) {}

void Channel::addOperater(int operater) { _operaters.push_back(operater); }

void Channel::addMember(const std::string& member) {
  _members.push_back(member);
}

void Channel::addInvitee(const std::string& member) {
  _invitees.push_back(member);
}

void Channel::removeOperater(int operater) { _operaters.remove(operater); }

void Channel::removeMember(const std::string& member) {
  _members.remove(member);
}

void Channel::removeInvitee(const std::string& member) {
  _invitees.remove(member);
}

void Channel::setMode(const char mode) { _mode = mode; }

void Channel::setLimit(size_t limit) { _limit = limit; }

void Channel::setName(const std::string& name) { _name = name; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

void Channel::setPassword(const std::string& password) { _password = password; }

char Channel::getMode() const { return _mode; }

size_t Channel::getLimit() const { return _limit; }

const std::string& Channel::getName() const { return _name; }

const std::string& Channel::getTopic() const { return _topic; }

const std::string& Channel::getPassword() const { return _password; }

const std::list<int>& Channel::getOperaters() const { return _operaters; }

const std::list<std::string>& Channel::getMembers() const { return _members; }

const std::list<std::string>& Channel::getInvitees() const { return _invitees; }