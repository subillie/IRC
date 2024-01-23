#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include <functional>
#include <map>
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
  RequestHandler(int clientFd, std::string request);  // init map
  // void parse(std::string request);
  void privmsg(int fd, std::vector<std::string> token);
  void join(int fd, std::vector<std::string> token);
  void init();
  void execute();  // execute command and handle errors
};

#endif