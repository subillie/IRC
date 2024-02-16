#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <ctime>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include "../Server/Server.hpp"

#define INVITE_ONLY_CHANNEL 'i'
#define PROTECTED_TOPIC 't'
#define KEY_CHANNEL 'k'
#define CLIENT_LIMIT_CHANNEL 'l'

class Messenger;

class Channel {
 private:
  size_t _limit;
  std::string _name;
  std::string _topic;
  std::string _password;
  std::set<char> _modes;
  std::set<std::string> _ops;
  std::set<std::string> _members;
  std::set<std::string> _invitees;
  std::string _creationTime;

 public:
  Channel(const char& mode, const std::string& name);

  void addMode(const char mode);
  void addOp(const std::string& op);
  void addMember(const std::string& member);
  void addInvitee(const std::string& member);
  void removeMode(const char& mode);
  void removeOp(const std::string& op);
  void removeMember(const std::string& member);
  void removeInvitee(const std::string& member);

  void setLimit(size_t limit);
  void setName(const std::string& name);
  void setTopic(const std::string& topic);
  void setPassword(const std::string& password);
  size_t getLimit() const;
  const std::string& getName() const;
  const std::string& getTopic() const;
  const std::string& getPassword() const;
  const std::string& getCreationTime() const;
  const std::set<char>& getModes() const;
  const std::set<std::string>& getOps() const;
  const std::set<std::string>& getMembers() const;
  const std::set<std::string>& getInvitees() const;
  bool isFull() const;
  bool isOp(const std::string& nick) const;
  bool isMember(const std::string& nick) const;
  bool isInvitee(const std::string& nick) const;
  bool isMode(const char& mode) const;
};

std::ostream& operator<<(std::ostream& os, const Channel& channel);

#endif