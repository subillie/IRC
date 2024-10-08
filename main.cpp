#include <signal.h>

#include "Channel/Channel.hpp"
#include "Client/Client.hpp"
#include "Macros/Characters.hpp"
#include "Server/Server.hpp"

std::string Server::_serverCreated;
std::map<int, Client *> Server::_clientFds;
std::map<std::string, Client *> Server::_clientNicks;
std::map<std::string, Channel *> Server::_channelNames;

void signalHandler(int signum) { (void)signum; }

int getPort(const std::string &port) {
  if (port.empty() || port.length() > 5) {
    throw std::runtime_error("Wrong port number");
  }
  size_t found = port.find_first_not_of(DIGIT);
  if (found != std::string::npos) {
    throw std::runtime_error("Wrong port number");
  }
  int portNum = atoi(port.c_str());
  if (portNum < 0 || portNum > 65535)
    throw std::runtime_error("Wrong port number");
  return portNum;
}

void isValidPassword(const std::string &pw) {
  if (pw.length() > 10) {
    throw std::runtime_error("Password maximum length: 10");
  }
  if (pw.find_first_not_of(LOWERCASE + UPPERCASE + DIGIT) !=
      std::string::npos) {
    throw std::runtime_error("Valid password format : [a-z], [A-Z], [digits]");
  }
}

int main(int ac, char **av) {
  if (ac != 3) {
    std::cerr << RED << "Usage: ./ircserver <port> <password>" << std::endl;
    return 1;
  }
  signal(SIGPIPE, signalHandler);
  try {
    isValidPassword(av[2]);
    Server server(getPort(av[1]), av[2]);
    server.run();
  } catch (std::exception &e) {
    std::cerr << RED << e.what() << std::endl;
  }
  return 0;
}