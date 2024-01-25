#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include "ErrorMacros.hpp"

class ErrorHandler {
 private:
  int _fd;

 public:
  ErrorHandler();
  ErrorHandler(int fd);
  void ErrNeedMoreParams();
  void ErrAlreadyRegistered();
  void ErrPasswdMismatch();
  void setFd(int fd);
};

#endif