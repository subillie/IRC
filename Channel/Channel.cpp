#include "Channel.hpp"

#include "../RequestHandler/Messenger/Messenger.hpp"

Channel::Channel(const char& mode, const std::string& name)
    : _limit(0), _name(name) {
  time_t now;
  time(&now);

  size_t t = static_cast<size_t>(now);
  std::stringstream ss;
  ss << t;
  _creationTime = ss.str();
  _modes.insert(mode);
}

void Channel::addMode(const char mode) { _modes.insert(mode); }

void Channel::addOp(const std::string& op) { _ops.insert(op); }

void Channel::addMember(const std::string& member) { _members.insert(member); }

void Channel::addInvitee(const std::string& member) {
  _invitees.insert(member);
}

void Channel::removeMode(const char& mode) { _modes.erase(mode); }

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

bool Channel::isFull() const { return _limit <= _members.size(); }

bool Channel::isOp(const std::string& nick) const {
  return _ops.find(nick) != _ops.end();
}

bool Channel::isMember(const std::string& nick) const {
  return _members.find(nick) != _members.end();
}

bool Channel::isInvitee(const std::string& nick) const {
  return _invitees.find(nick) != _invitees.end();
}

bool Channel::isMode(const char& mode) const {
  return _modes.find(mode) != _modes.end();
}

// void Channel::sendToAll(Messenger& msg) const {
//   for (std::set<std::string>::const_iterator it = _members.begin();
//        it != _members.end(); it++) {
//     Messenger copy = msg;
//     copy.addRespondToClient(Server::_clientNicks[*it]->getFd());
//   }
// }

std::ostream& operator<<(std::ostream& os, const Channel& channel) {
  os << "====Channel====\n";
  os << "Name : " << channel.getName() << "\n";
  os << "Topic : " << channel.getTopic() << "\n";
  os << "Password : " << channel.getPassword() << "\n";
  os << "Creation Time : " << channel.getCreationTime() << "\n";
  os << "Limit : " << channel.getLimit() << "\n";
  os << "Modes : ";
  std::set<char> modes = channel.getModes();
  std::set<char>::iterator it = modes.begin();
  for (; it != modes.end(); it++) {
    os << *it << " ";
  }
  os << "\n";
  os << "Ops : ";
  std::set<std::string> ops = channel.getOps();
  std::set<std::string>::iterator it2 = ops.begin();
  for (; it2 != ops.end(); it2++) {
    os << *it2 << " ";
  }
  os << "\n";
  os << "Members : ";
  std::set<std::string> members = channel.getMembers();
  std::set<std::string>::iterator it3 = members.begin();
  for (; it3 != members.end(); it3++) {
    os << *it3 << " ";
  }
  os << "\n";
  os << "Invitees : ";
  std::set<std::string> invitees = channel.getInvitees();
  std::set<std::string>::iterator it4 = invitees.begin();
  for (; it4 != invitees.end(); it4++) {
    os << *it4 << " ";
  }
  os << "\n";
  os << "================\n";
  return os;
}