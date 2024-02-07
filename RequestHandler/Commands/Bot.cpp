#include "../RequestHandler.hpp"

void RequestHandler::bgp(const std::set<std::string>& memberList) {
  const std::string menuMorning[] = {"cereal🥣",       "salad🥗",
                                     "french toast🍞", "yogurt🥛",
                                     "pancake🥞",      "scrambled egg🥚"};
  const std::string menuLunch[] = {"sandwich🥪", "tomato pasta🍝",  "omurice🍳",
                                   "donkatsu🍛", "dooboo kimchi🍽️", "pizza🍕"};
  const std::string menuDinner[] = {"burger🍔",        "sushi🍣",
                                    "pho🍲",           "gambas🦐",
                                    "kimchi jjigae🥘", "samgyeopsal🥩"};
  const std::string menuDawn[] = {"chicken🍗",  "ramyeon🍜",  "jokbal🐷",
                                  "bibimbap🥢", "tanghuru🍓", "french fries🍟"};

  time_t now;
  time(&now);
  struct tm* timeInfo = localtime(&now);
  int hour = timeInfo->tm_hour;

  srand((unsigned int)time(NULL));
  int random = rand() % 6;
  std::string bgp;
  if (hour >= 6 && hour < 11)
    bgp = menuMorning[random];
  else if (hour >= 11 && hour < 16)
    bgp = menuLunch[random];
  else if (hour >= 16 && hour < 22)
    bgp = menuDinner[random];
  else
    bgp = menuDawn[random];
  bgp = "What about... <" + bgp + "> !!!!";

  std::set<std::string>::const_iterator it;
  for (it = memberList.begin(); it != memberList.end(); ++it) {
    _msg.setPrefix(_client->getPrefix());
    _msg.setParam("PRIVMSG " + _token[1]);
    _msg.setTrailing(bgp);
    _msg.sendToClient(Server::_clientNicks[*it]->getFd());
  }
}

void RequestHandler::rps(const std::set<std::string>& memberList) {
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