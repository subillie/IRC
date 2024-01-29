#include "../RequestHandler.hpp"

void RequestHandler::privmsg() {
  const std::string response =
      "Hello from the server!";  // client connection test
  _msg.sendToClient(_fd);
}