
#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _nickname(""), _isRegistered(false) {}

void Client::setUsername(const std::string &username) { _username = username; }

void Client::setNickname(const std::string &nickname) { _nickname = nickname; }

void Client::setPassword(const std::string &password) { _password = password; }

const int &Client::getFd() const { return _fd; }

const std::string &Client::getNickname() const { return _nickname; }

const std::string &Client::getPassword() const { return _password; }

const std::string &Client::getUsername() const { return _username; }

bool Client::getIsRegistered() const { return _isRegistered; }

void Client::setIsRegisterd(bool val) { _isRegistered = val; }