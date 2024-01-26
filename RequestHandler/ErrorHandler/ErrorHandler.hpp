#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include "ErrorMacros.hpp"

class ErrorHandler {
 private:
  int _fd;

 public:
  ErrorHandler();

  void ErrNeedMoreParams();
  void ErrAlreadyRegistered();
  void ErrPasswdMismatch();
  void ErrNoNickNameGiven();
  void ErrErroneusNickName();
  void ErrNickNameInUse();
  void ErrNoOrigin();
  void ErrUnknown();

  void setFd(int fd);

  void sendToClient();
};

#endif