#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include <sys/socket.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../Client/Client.hpp"
#include "../Macros/Replies.hpp"
#include "../Print/Print.hpp"
#include "ErrorHandler/ErrorHandler.hpp"

class RequestHandler {
 private:
  Client *_client;
  std::string _request;
  std::string _command;
  std::string _password;
  std::vector<std::string> _token;
  typedef void (RequestHandler::*CommandFunction)(void);
  std::map<std::string, CommandFunction> _commandMap;
  ErrorHandler _error;

  void cap();
  void nick();
  void user();
  void pass();
  void join();
  void privmsg();
  void kick();
  void invite();
  void topic();
  void mode();

 public:
  RequestHandler(Client *client, const std::string &request,
                 const std::string &password);  // Init map

  void parse();
  void execute();  // Execute commands and handle errors
};

#endif