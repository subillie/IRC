#include "ErrorHandler.hpp"

ErrorHandler::ErrorHandler() : _fd(0) {}

ErrorHandler::ErrorHandler(int fd) : _fd(fd) {}

void ErrorHandler::ErrNeedMoreParams() {}

void ErrorHandler::ErrAlreadyRegistered() {}

void ErrorHandler::ErrPasswdMismatch() {}

void ErrorHandler::setFd(int fd) { this->_fd = fd; }