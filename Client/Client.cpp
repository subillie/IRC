
#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _isAuthenticated(false) {}

const int &Client::getFd() const { return _fd; }

const std::string &Client::getNickname() const { return _nickname; }

const std::string &Client::getPassword() const { return _password; }

const std::string &Client::getUsername() const { return _username; }
