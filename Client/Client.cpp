
#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _nickname("*"), _isRegistered(false) {}

void Client::setMode(const std::string &mode) { _mode = mode; }

void Client::setUsername(const std::string &username) { _username = username; }

void Client::setNickname(const std::string &nickname) { _nickname = nickname; }

void Client::setPassword(const std::string &password) { _password = password; }

void Client::setHostname(const std::string &hostname) { _hostname = hostname; }

void Client::setRealname(const std::string &realname) { _realname = realname; }

void Client::addChannel(const std::string &channel) {
  _channels.insert(channel);
}

void Client::removeChannel(const std::string &channel) {
  _channels.erase(channel);
}

const int &Client::getFd() const { return _fd; }

const std::string &Client::getMode() const { return _mode; }

const std::string &Client::getNickname() const { return _nickname; }

const std::string &Client::getPassword() const { return _password; }

const std::string &Client::getUsername() const { return _username; }

const std::string &Client::getHostname() const { return _hostname; }

const std::string &Client::getRealname() const { return _realname; }

const std::string Client::getPrefix() const {
  return _nickname + "!" + _username + "@" + _hostname;
}

const std::set<std::string> &Client::getChannels() const { return _channels; }

bool Client::isMaxJoined() const { return _channels.size() == MAX_CHANNEL; }

bool Client::getIsRegistered() const { return _isRegistered; }

void Client::setIsRegisterd(bool val) { _isRegistered = val; }

std::ostream &operator<<(std::ostream &os, const Client &client) {
  os << "Client Information:" << std::endl;
  os << "File Descriptor: " << client.getFd() << std::endl;
  os << "Username: " << client.getUsername() << std::endl;
  os << "Nickname: " << client.getNickname() << std::endl;
  os << "Password: " << client.getPassword() << std::endl;
  os << "Is Registered: " << (client.getIsRegistered() ? "Yes" : "No")
     << std::endl;
  os << "Joined Channels: " << client.getChannels().size() << std::endl;
  return os;
}