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
  size_t _limit;
  std::string _name;
  std::string _topic;
  std::string _password;
  std::list<char> _modes;
  std::list<std::string> _operaters;
  std::list<std::string> _members;
  std::list<std::string> _invitees;

 public:
  Channel(const char& mode, const std::string& name);

  void addMode(const char mode);
  void addOperater(const std::string& operater);
  void addMember(const std::string& member);
  void addInvitee(const std::string& member);
  void removeOperater(const std::string& operater);
  void removeMember(const std::string& member);
  void removeInvitee(const std::string& member);  // TODO: 필요한가?

  void setLimit(size_t limit);
  void setName(const std::string& name);
  void setTopic(const std::string& topic);
  void setPassword(const std::string& password);
  size_t getLimit() const;
  const std::string& getName() const;
  const std::string& getTopic() const;
  const std::string& getPassword() const;
  const std::list<char>& getModes() const;
  const std::list<std::string>& getOperaters() const;
  const std::list<std::string>& getMembers() const;
  const std::list<std::string>& getInvitees() const;
};

#endif