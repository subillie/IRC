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
#include "../Macros/Characters.hpp"
#include "../Macros/Replies.hpp"
#include "../Print/Print.hpp"
#include "../Server/Server.hpp"
#include "ErrorHandler/ErrorHandler.hpp"
#include "Messenger/Messenger.hpp"

class RequestHandler {
 private:
  int _fd;
  Client *_client;
  std::string _request;
  std::string _command;
  std::string _password;
  std::vector<std::string> _token;
  typedef void (RequestHandler::*CommandFunction)(void);
  std::map<std::string, CommandFunction> _commandMap;
  ErrorHandler _error;  // Messenger _messenger

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
  void pong();

 public:
  RequestHandler(Client *client, const std::string &request,
                 const std::string &password);  // Init map

  void parse();
  void execute();  // Execute commands and handle errors
  void sendToClient(int socket, const std::string &msg);
};

#endif

// Command 관련
//  TODO :
//  1. PASS, NICK, USER 명령어 순서 체크를 서버에서 해야되나...? (클라이언트에서
//  해주나?)
//  2. PASS, NICK, USER에 해당하는 정보가 다 있는지 확인 절차 필요하나...? (유저
//  인증 체크)