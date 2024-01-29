#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <sys/socket.h>

#include <string>
#include <vector>

#include "../../Client/Client.hpp"
#include "../../Macros/Characters.hpp"
#include "../../Server/Server.hpp"
#include "ErrorMacros.hpp"
#include "ReplyMacros.hpp"

class Messenger {
 private:
  std::string _prefix;
  std::string _param;
  std::string _trailing;

 public:
  Messenger();
  // Error function
  void ErrNoSuchChannel(int fd);                               // 403
  void ErrTooManyChannels(int fd);                             // 405
  void ErrNoOrigin(int fd);                                    // 409
  void ErrUnknownCommand(int fd, const std::string& command);  // 421
  void ErrNoNickNameGiven(int fd);                             // 431
  void ErrErroneusNickName(int fd, const std::string& nick);   // 432
  void ErrNickNameInUse(int fd, const std::string& nick);      // 433
  void ErrNotRegistered(int fd);                               // 451
  void ErrNeedMoreParams(int fd, const std::string& command);  // 461
  void ErrAlreadyRegistered(int fd);                           // 462
  void ErrPasswdMismatch(int fd);                              // 464
  void ErrChannelIsFull(int fd, const std::string& channel);   // 471
  void ErrInviteOnlyChan(int fd, const std::string& channel);  // 473
  void ErrBadChannelKey(int fd, const std::string& channel);   // 475
  void ErrBadChanMask(int fd);                                 // 476
  void ErrUnexpected(int fd);  // 에러코드가 정해져 있지 않은 에러
  // Reply function
  void RplWelcome(int fd);   // 001
  void RplYourHost(int fd);  // 002
  void RplCreated(int fd);   // 003
  void RplMyinfo(int fd);    // 004
  void RplTopic(int fd, const std::string& channel,
                const std::string& topic);                 // 332
  void RplInviteList(int fd, const std::string& channel);  // 336
  void RplNamReply(int fd, const std::string& channel,
                   const std::string& nick);               // 353
  void RplEndOfNames(int fd, const std::string& channel);  // 366
  //  make response
  void setPrefix(const std::string& prefix);
  void setParam(const std::string& param);
  void setTrailing(const std::string& trailing);
  void sendToClient(int fd);
};

#endif