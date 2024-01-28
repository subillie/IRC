#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <list>
#include <string>
#include <vector>

#define DEFAULT 'd'
#define INVITE_ONLY_CHANNEL 'i'
#define PROTECTED_TOPIC 't'
#define KEY_CHANNEL 'k'
#define CLIENT_LIMIT_CHANNEL 'l'

class Client;

class Channel {
 private:
  char _mode;
  size_t _limit;
  std::string _name;
  std::string _topic;
  std::string _password;
  std::list<int> _operaters;
  std::list<std::string> _members;
  std::list<std::string> _invitees;

 public:
  Channel(const char, const std::string& name);

  void addOperater(int operater);
  void addMember(const std::string& member);
  void addInvitee(const std::string& member);
  void removeOperater(int operater);
  void removeMember(const std::string& member);
  void removeInvitee(const std::string& member);  // TODO: 필요한가?

  void setMode(const char mode);
  void setLimit(size_t limit);
  void setName(const std::string& name);
  void setTopic(const std::string& topic);
  void setPassword(const std::string& password);
  char getMode() const;
  size_t getLimit() const;
  const std::string& getName() const;
  const std::string& getTopic() const;
  const std::string& getPassword() const;
  const std::list<int>& getOperaters() const;
  const std::list<std::string>& getMembers() const;
  const std::list<std::string>& getInvitees() const;
};

#endif