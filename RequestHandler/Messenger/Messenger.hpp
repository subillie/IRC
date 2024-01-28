#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <sys/socket.h>

#include <string>
#include <vector>

#include "../../Client/Client.hpp"
#include "../../Macros/Characters.hpp"
#include "../../Server/Server.hpp"
#include "ErrorMacros.hpp"
#include "Replies.hpp"

class Messenger {
 private:
  std::string _prefix;
  std::string _param;
  std::string _trailing;

 public:
  Messenger();
  // Error function
  void ErrNoSuchChannel(int fd);      // 403
  void ErrNoOrigin(int fd);           // 409
  void ErrUnknownCommand(int fd);     // 421
  void ErrNoNickNameGiven(int fd);    // 431
  void ErrErroneusNickName(int fd);   // 432
  void ErrNickNameInUse(int fd);      // 433
  void ErrNeedMoreParams(int fd);     // 461
  void ErrAlreadyRegistered(int fd);  // 462
  void ErrPasswdMismatch(int fd);     // 464
  void ErrUnexpected(int fd);  // 에러코드가 정해져 있지 않은 에러
  // Reply function
  void RplWelcome(int fd);   // 001
  void RplYourHost(int fd);  // 002
  void RplCreated(int fd);   // 003
  void RplMyinfo(int fd);    // 004
  //  make response
  void setPrefix(const std::string& prefix);
  void setParam(const std::string& param);
  void setTrailing(const std::string& trailing);
  void sendToClient(int fd);
};

#endif