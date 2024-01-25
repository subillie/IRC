#include <signal.h>

#include <iostream>

#include "Server/Server.hpp"

std::map<int, Client *> Server::_clientFds;
std::map<std::string, Client *> Server::_clientNicks;
std::map<std::string, Channel *> Server::_channelNames;

void signalHandler(int signum) { (void)signum; }

int getPort(std::string port) {
  if (port.empty() || port.length() > 5) {
    throw std::runtime_error("Wrong port number");
  }
  size_t found = port.find_first_not_of("0123456789");
  if (found != std::string::npos) {
    throw std::runtime_error("Wrong port number");
  }
  int portNum = atoi(port.c_str());
  if (portNum < 0 || portNum > 65535)
    throw std::runtime_error("Wrong port number");
  return portNum;
}

int main(int ac, char **av) {
  if (ac != 3) {
    std::cerr << RED << "Usage: ./ircserver <port> <password>" << std::endl;
    return 1;
  }
  signal(SIGINT, signalHandler);
  try {
    Server server(getPort(av[1]), av[2]);
    server.run();
  } catch (std::exception &e) {
    std::cerr << RED << e.what() << std::endl;
  }
  return 0;
}