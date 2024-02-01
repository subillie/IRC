#include <signal.h>

#include <iostream>

#include "Client/Client.hpp"
#include "Macros/Characters.hpp"
#include "Server/Server.hpp"

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
    throw std::runtime_error("Password should be no more than 10 characters");
  }
  if (pw.find_first_not_of(LOWERCASE + UPPERCASE + DIGIT) !=
      std::string::npos) {
    throw std::runtime_error("Valid password format : [a-z], [A-Z], [digits]");
  }
}

void deleteMap(void) {
  std::map<int, Client *>::iterator client;
  for (client = Server::_clientFds.begin(); client != Server::_clientFds.end();
       ++client) {
    close(client->second->getFd());
    delete (client->second);
  }
  Server::_clientFds.clear();
  Server::_clientNicks.clear();
  std::map<std::string, Channel *>::iterator channel;
  for (channel = Server::_channelNames.begin();
       channel != Server::_channelNames.end(); ++channel) {
    delete (channel->second);
  }
  Server::_channelNames.clear();
}

int main(int ac, char **av) {
  if (ac != 3) {
    std::cerr << RED << "Usage: ./ircserver <port> <password>" << std::endl;
    return 1;
  }
  signal(SIGINT, signalHandler);
  try {
    isValidPassword(av[2]);
    Server server(getPort(av[1]), av[2]);
    server.run();
  } catch (std::exception &e) {
    std::cerr << RED << e.what() << std::endl;
    // TODO : free all
  }
  deleteMap();
  return 0;
}