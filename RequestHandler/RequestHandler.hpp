#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include <sys/socket.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../Channel/Channel.hpp"
#include "../Client/Client.hpp"
#include "../Macros/Characters.hpp"
#include "../Print/Print.hpp"
#include "../Server/Server.hpp"
#include "Messenger/Messenger.hpp"

class RequestHandler {
 private:
  int _fd;
  Messenger _msg;
  Client *_client;
  std::string _request;
  std::string _command;
  const std::string _password;
  std::vector<std::string> _token;
  typedef void (RequestHandler::*CommandFunction)(void);
  std::map<std::string, CommandFunction> _commandMap;

  void cap();
  void nick();
  void user();
  void pass();

  void join();
  void privmsg();
  void kick();
  void invite();
  void topic();

  void userMode(const std::string &target);
  void channelMode(const std::string &target);
  void mode();
  void pong();

 public:
  RequestHandler(Client *client, const std::string &request,
                 const std::string &password);  // Init map

  void parse();
  void execute();  // Execute commands and handle errors
};

#endif
