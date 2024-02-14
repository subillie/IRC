#include "../RequestHandler.hpp"

// CAP LS
void RequestHandler::cap() {
  if (_token[1] == "LS") {
    _msg.setPrefix(SERVER);
    _msg.setParam("CAP * LS :");
    _msg.addRespondToClient(_fd);
  }
}