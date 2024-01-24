#include <signal.h>

#include <iostream>

#include "Server/Server.hpp"

std::map<int, Client *> Server::_clientFds;
std::map<std::string, Client *> Server::_clientNicks;
std::map<std::string, Channel *> Server::_channelNames;

void signalHandler(int signum) { (void)signum; }

int main(int ac, char **av) {
  if (ac != 3) {
    std::cerr << "Usage: ./ircserver <port> <password>" << std::endl;
    return (1);
  }
  signal(SIGINT, signalHandler);
  try {
    Server server(av[1], av[2]);
    server.run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}