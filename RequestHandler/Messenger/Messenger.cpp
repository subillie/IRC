#include "Messenger.hpp"

Messenger::Messenger() : _prefix(""), _param(""), _trailing("") {}

void Messenger::setPrefix(const std::string& prefix) { _prefix = prefix; }

void Messenger::setParam(const std::string& param) { _param = param; }

void Messenger::setTrailing(const std::string& trailing) {
  _trailing = trailing;
}

void Messenger::sendToClient(int fd) {
  if (!_prefix.empty()) _prefix = ":" + _prefix + " ";
  if (!_trailing.empty()) _trailing = " :" + _trailing;
  std::string response = _prefix + _param + _trailing + CRLF;
  printCyan(response);
  if (send(fd, response.c_str(), response.length(), 0) == -1) {
    throw fd;
  }
  _prefix.clear();
  _param.clear();
  _trailing.clear();
}

const std::string& Messenger::getPrefix() const { return _prefix; }

const std::string& Messenger::getParam() const { return _param; }

const std::string& Messenger::getTrailing() const { return _trailing; }
