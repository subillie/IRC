#include "ErrorHandler.hpp"

ErrorHandler::ErrorHandler() : _fd(0) {}

void ErrorHandler::ErrNoSuchChannel() {}

void ErrorHandler::ErrNoOrigin() {}

void ErrorHandler::ErrNoNickNameGiven() {}

void ErrorHandler::ErrErroneusNickName() {}

void ErrorHandler::ErrNickNameInUse() {}

void ErrorHandler::ErrNeedMoreParams() {}

void ErrorHandler::ErrAlreadyRegistered() {}

void ErrorHandler::ErrPasswdMismatch() {}

void ErrorHandler::ErrUnknown() {}

void ErrorHandler::setFd(int fd) { this->_fd = fd; }