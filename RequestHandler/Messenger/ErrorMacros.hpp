#ifndef ERROR_MACROS_HPP
#define ERROR_MACROS_HPP

#include <string>
// Errors
#define ERR_NOORIGIN std::string("409")

#define ERR_UNKNOWNCOMMAND std::string("421")
#define ERR_NONICKNAMEGIVEN std::string("431")
#define ERR_ERRONEUSNICKNAME std::string("432")
#define ERR_NICKNAMEINUSE std::string("433")

#define ERR_NEEDMOREPARAMS std::string("461")
#define ERR_ALREADYREGISTERED std::string("462")
#define ERR_PASSWDMISMATCH std::string("464")

#endif