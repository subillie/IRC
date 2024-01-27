#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include "ErrorMacros.hpp"

class ErrorHandler {
 private:
  int _fd;

 public:
  ErrorHandler();

  void ErrNoSuchChannel();      // 403
  void ErrNoOrigin();           // 409
  void ErrNoNickNameGiven();    // 431
  void ErrErroneusNickName();   // 432
  void ErrNickNameInUse();      // 433
  void ErrNeedMoreParams();     // 461
  void ErrAlreadyRegistered();  // 462
  void ErrPasswdMismatch();     // 464
  void ErrUnknown();

  void setFd(int fd);

  void sendToClient();
};

#endif