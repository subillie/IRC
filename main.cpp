#include <signal.h>

#include <iostream>

#include "Server/Server.hpp"

std::map<int, Client *> Server::_clientFds;
std::map<std::string, Client *> Server::_clientNicks;
std::map<std::string, Channel *> Server::_channelNames;

void signalHandler(int signum) { (void)signum; }

int getPort(char *port) {
  size_t len = strlen(port);
  for (size_t i = 0; i < len; i++) {
    if (!isdigit(port[i])) {
      throw std::runtime_error("Wrong port number");
    }
  }
  int portNum = atoi(port);
  if (portNum < 0 || portNum > 65535)
    throw std::runtime_error("Wrong port number");
  return portNum;
}

int main(int ac, char **av) {
  if (ac != 3) {
    std::cerr << "Usage: ./ircserver <port> <password>" << std::endl;
    return 1;
  }
  signal(SIGINT, signalHandler);
  try {
    int portNum = getPort(av[1]);
    Server server(portNum, av[2]);
    server.run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}