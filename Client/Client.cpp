#include "Client.hpp"

Client::Client(int fd)
    : _fd(fd), _isRegistered(false), _isQuit(false), _nickname("*") {}

bool Client::isMaxJoined() const { return _channels.size() == MAX_CHANNEL; }

void Client::addChannel(const std::string &channel) {
  _channels.insert(channel);
}

void Client::leaveChannel(Channel *channel) {
  // Client의 채널 목록에서 제거
  std::string channelName = channel->getName();
  _channels.erase(channelName);

  // 채널의 Client 목록에서 제거
  channel->removeOp(_nickname);
  channel->removeInvitee(_nickname);
  channel->removeMember(_nickname);

  // 빈 채널이 되면 채널 삭제
  if (channel->getMembers().empty()) {
    Server::_channelNames.erase(channelName);
    delete channel;
    channel = NULL;
  }
}

void Client::setIsRegistered(bool val) { _isRegistered = val; }

void Client::setisQuit(bool val) { _isQuit = val; }

void Client::setMode(const std::string &mode) { _mode = mode; }

void Client::setUsername(const std::string &username) { _username = username; }

void Client::setNickname(const std::string &nickname) { _nickname = nickname; }

void Client::setPassword(const std::string &password) { _password = password; }

void Client::setHostname(const std::string &hostname) { _hostname = hostname; }

void Client::setRealname(const std::string &realname) { _realname = realname; }

const int &Client::getFd() const { return _fd; }

bool Client::getIsRegistered() const { return _isRegistered; }

bool Client::getisQuit() const { return _isQuit; };

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

void Client::sendResponds() {
  while (!_responds.empty()) {
    std::string response = _responds.front();
    printRed(response);
    if (send(_fd, response.c_str(), response.length(), 0) == -1) {
      printRed(response);
      throw _fd;
    }
    _responds.pop();
  }
  if (_isQuit) {
    throw _fd;
  }
}

void Client::addResponds(const std::string &responds) {
  _responds.push(responds);
}

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