#include <signal.h>

#include <iostream>

#include "Server.hpp"

void signalHandler(int signum) { (void)signum; }

int main(int ac, char **av) {
  if (ac != 3) {
    std::cerr << "Usage: ./ircserver <port> <password>" << std::endl;
    return (1);
  }

  signal(SIGINT, signalHandler);
  Server server(av[1], av[2]);
  server.run();
  return 0;
}