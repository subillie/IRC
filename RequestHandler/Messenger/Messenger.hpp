#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <sys/socket.h>

#include <string>
#include <vector>

#include "../../Channel/Channel.hpp"
#include "../../Client/Client.hpp"
#include "../../Macros/Characters.hpp"
#include "../../Print/Print.hpp"
#include "../../Server/Server.hpp"
#include "ErrorMacros.hpp"
#include "ReplyMacros.hpp"

class Messenger {
 private:
  std::string _prefix;
  std::string _param;
  std::string _trailing;
  fd_set _writeSet;

 public:
  Messenger();
  // Error function
  void ErrNoSuchNick(int fd, const std::string& nick);           // 401
  void ErrNoSuchChannel(int fd, const std::string& channel);     // 403
  void ErrCannotSendToChan(int fd, const std::string& channel);  // 404
  void ErrTooManyChannels(int fd, const std::string& channel);   // 405
  void ErrNoOrigin(int fd);                                      // 409
  void ErrNoRecipient(int fd);                                   // 411
  void ErrNoTextToSend(int fd);                                  // 412
  void ErrUnknownCommand(int fd, const std::string& command);    // 421
  void ErrNoNickNameGiven(int fd);                               // 431
  void ErrErroneusNickName(int fd, const std::string& nick);     // 432
  void ErrNickNameInUse(int fd, const std::string& nick);        // 433
  void ErrUserNotInChannel(int fd, const std::string& nick,
                           const std::string& channel);      // 441
  void ErrNotOnChannel(int fd, const std::string& channel);  // 442
  void ErrUserOnChannel(int fd, const std::string& nick,
                        const std::string& channel);             // 443
  void ErrNotRegistered(int fd);                                 // 451
  void ErrNeedMoreParams(int fd, const std::string& command);    // 461
  void ErrAlreadyRegistered(int fd);                             // 462
  void ErrPasswdMismatch(int fd);                                // 464
  void ErrKeySet(int fd, const std::string& channel);            // 467
  void ErrChannelIsFull(int fd, const std::string& channel);     // 471
  void ErrUnknownMode(int fd, const std::string& mode);          // 472
  void ErrInviteOnlyChan(int fd, const std::string& channel);    // 473
  void ErrBadChannelKey(int fd, const std::string& channel);     // 475
  void ErrBadChanMask(int fd);                                   // 476
  void ErrChanOPrivsNeeded(int fd, const std::string& channel);  // 482
  void ErrUModeUnknownFlag(int fd);                              // 501
  void ErrUsersDontMatch(int fd);                                // 502
  void ErrInvalidKey(int fd, const std::string& channel);        // 525
  void ErrInvalidModeParam(int fd, const std::string& channel,
                           const char& mode);  // 696
  void ErrUnexpected();  // 에러코드가 정해져 있지 않은 에러

  // Reply function
  void RplWelcome(int fd);                                    // 001
  void RplYourHost(int fd);                                   // 002
  void RplCreated(int fd);                                    // 003
  void RplMyinfo(int fd);                                     // 004
  void RplISupport(int fd);                                   // 005
  void RplUModeIs(int fd, const std::string& usermode);       // 221
  void RplEndOfWho(int fd, const std::string& mask);          // 315
  void RplEndOfWhoIs(int fd, const std::string& client);      // 318
  void RplChannelModeIs(int fd, const std::string& channel);  // 324
  void RplCreationTime(int fd, const std::string& channel);   // 324
  void RplNoTopic(int fd, const std::string& channel);        // 331
  void RplTopic(int fd, const std::string& channel,
                const std::string& topic);                 // 332
  void RplInviteList(int fd, const std::string& channel);  // 336
  void RplInviting(int fd, const std::string& invitee,
                   const std::string& channel);  // 341
  void RplWhoReply(int fd, const std::string& mask, const std::string& channel,
                   const std::string& flag);                 // 352
  void RplNamReply(int fd, const std::string& channel);      // 353
  void RplEndOfNames(int fd, const std::string& channel);    // 366
  void RplEndOfBanList(int fd, const std::string& channel);  // 368

  //  make reply
  void setPrefix(const std::string& prefix);
  void setParam(const std::string& param);
  void setTrailing(const std::string& trailing);
  void addReplyToClient(int fd);
  void addReplyToChannel(Channel* channel);

  // getter
  const std::string& getPrefix() const;
  const std::string& getParam() const;
  const std::string& getTrailing() const;
  const fd_set& getWriteSet() const;

  void addWriteSet(int fd);
};

#endif