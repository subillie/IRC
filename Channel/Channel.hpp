#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <list>
#include <string>
#include <vector>

class Client;

class Channel {
 private:
  std::string _name;
  std::list<std::string> _members;
  std::list<int> _operaters;

 public:
  Channel(const std::string& name);
};

#endif