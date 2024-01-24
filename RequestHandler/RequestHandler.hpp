#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include <sys/socket.h>

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class RequestHandler {
 private:
  int _clientFd;
  std::string _request;
  std::vector<std::string> _token;
  typedef void (RequestHandler::*CommandFunction)(int,
                                                  std::vector<std::string>);
  std::map<std::string, CommandFunction> _commandMap;

 public:
  RequestHandler(int clientFd, const std::string &request);  // init map
  void parse();
  void execute();  // execute command and handle errors
  void join(int fd, std::vector<std::string> token);
  void privmsg(int fd, std::vector<std::string> token);
};

#endif