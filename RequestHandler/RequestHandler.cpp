#include "RequestHandler.hpp"

RequestHandler::RequestHandler(Client* client, const std::string& request,
                               const std::string& password)
    : _fd(client->getFd()),
      _client(client),
      _request(request),
      _password(password) {
  _commandMap["CAP"] = &RequestHandler::cap;
  _commandMap["PASS"] = &RequestHandler::pass;
  _commandMap["NICK"] = &RequestHandler::nick;
  _commandMap["USER"] = &RequestHandler::user;
  _commandMap["JOIN"] = &RequestHandler::join;
  _commandMap["PRIVMSG"] = &RequestHandler::privmsg;
  _commandMap["MODE"] = &RequestHandler::mode;
  _commandMap["PING"] = &RequestHandler::pong;
  _commandMap["KICK"] = &RequestHandler::kick;
  _commandMap["INVITE"] = &RequestHandler::invite;
  _commandMap["PART"] = &RequestHandler::part;
  _commandMap["TOPIC"] = &RequestHandler::topic;
  _commandMap["QUIT"] = &RequestHandler::quit;
  _commandMap["WHO"] = &RequestHandler::who;
  _commandMap["WHOIS"] = &RequestHandler::whois;
}

void RequestHandler::parse() {
  std::cout << _request << std::endl;
  std::stringstream ss(_request);
  std::string str;
  while (getline(ss, str, ' ')) {
    if (str.find(":") != std::string::npos) {
      str.erase(0, 1);
      std::string remainer;
      getline(ss, remainer);
      if (!remainer.empty())
        _token.push_back(str + " " + remainer);
      else
        _token.push_back(str);
      break;
    }
    _token.push_back(str);
  }
  _command = _token[0];
}

void RequestHandler::execute() {
  if (_request.empty()) {
    return;
  }
  parse();
  std::map<std::string, RequestHandler::CommandFunction>::iterator found =
      _commandMap.find(_command);
  if (found == _commandMap.end()) {
    _msg.ErrUnknownCommand(_fd, _command);
    return;
  }
  if (!isConnectionMsgs() && !_client->getIsRegistered()) {
    _msg.ErrNotRegistered(_fd);
    return;
  }
  (this->*(found->second))();
  if (_client->getNickname() != "*" && !_client->getHostname().empty() &&
      !_client->getPassword().empty() && !_client->getIsRegistered()) {
    _msg.RplWelcome(_fd);
    _msg.RplYourHost(_fd);
    _msg.RplCreated(_fd);
    _msg.RplMyinfo(_fd);
    _msg.RplISupport(_fd);
    _client->setIsRegistered(true);
  }
}

bool RequestHandler::isConnectionMsgs() {
  return (_command == "USER" || _command == "NICK" || _command == "PING" ||
          _command == "CAP" || _command == "PASS" || _command == "QUIT");
}

const fd_set& RequestHandler::getMsgWriteSet() const {
  return (_msg.getWriteSet());
};

bool RequestHandler::isInSameChannel(Client* c1, Client* c2) {
  std::set<std::string> chanC1 = c1->getChannels();
  std::set<std::string> chanC2 = c2->getChannels();
  for (std::set<std::string>::iterator it1 = chanC1.begin();
       it1 != chanC1.end(); it1++) {
    for (std::set<std::string>::iterator it2 = chanC2.begin();
         it2 != chanC2.end(); it2++) {
      if (*it1 == *it2) return true;
    }
  }
  return false;
}