#include "../RequestHandler.hpp"

void RequestHandler::bot(const std::set<std::string>& memberList) {
  srand((unsigned int)time(NULL));
  std::string rps;
  int random = rand() % 3;
  if (random == 0) {
    rps = "👊";
  } else if (random == 1) {
    rps = "📄";
  } else {
    rps = "💇";
  }
  std::set<std::string>::const_iterator it;
  for (it = memberList.begin(); it != memberList.end(); ++it) {
    _msg.setPrefix(_client->getPrefix());
    _msg.setParam("PRIVMSG " + _token[1]);
    _msg.setTrailing(rps);
    _msg.sendToClient(Server::_clientNicks[*it]->getFd());
  }
}