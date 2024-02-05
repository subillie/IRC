#include "../RequestHandler.hpp"

void RequestHandler::bot(const std::set<std::string>& memberList) {
  srand((unsigned int)time(NULL));
  std::string rps;
  int random = rand() % 3;
  if (random == 0) {
    rps = rock();
  } else if (random == 1) {
    rps =  paper();
  } else {
    rps = scissors();
  }
  std::set<std::string>::const_iterator it;
	for (it = memberList.begin(); it != memberList.end(); ++it) {
		_msg.setPrefix(_client->getNickname() + "!" + _client->getUsername() +
										"@" + _client->getHostname());
		_msg.setParam("PRIVMSG " + _token[1]);
		_msg.setTrailing(rps);
		_msg.sendToClient(Server::_clientNicks[*it]->getFd());
	}
}

const std::string RequestHandler::rock() {
  const std::string rock = "👊";
  return rock;
}

const std::string RequestHandler::paper() {
  const std::string paper = "📄";
  return paper;
}

const std::string RequestHandler::scissors() {
  const std::string scissors = "💇";
  return scissors;
}