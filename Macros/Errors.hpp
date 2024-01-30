#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>

#define ERR_NOSUCHNICK std::string("401")
#define ERR_NOSUCHCHANNEL std::string("403")
#define ERR_CANNOTSENDTOCHAN std::string("404")
#define ERR_TOOMANYCHANNELS std::string("405")

#define ERR_NOORIGIN std::string("409")
#define ERR_NORECIPIENT std::string("411")
#define ERR_NOTEXTTOSEND std::string("412")
#define ERR_UNKNOWNCOMMAND std::string("421")
#define ERR_NONICKNAMEGIVEN std::string("431")
#define ERR_ERRONEUSNICKNAME std::string("432")
#define ERR_NICKNAMEINUSE std::string("433")

#define ERR_NOTONCHANNEL std::string("442")
#define ERR_USERONCHANNEL std::string("443")

#define ERR_NOTREGISTERED std::string("451")

#define ERR_NEEDMOREPARAMS std::string("461")
#define ERR_ALREADYREGISTERED std::string("462")
#define ERR_PASSWDMISMATCH std::string("464")

#define ERR_CHANNELISFULL std::string("471")
#define ERR_UNKNOWNMODE std::string("472")
#define ERR_INVITEONLYCHAN std::string("473")
#define ERR_BADCHANNELKEY std::string("475")
#define ERR_BADCHANMASK std::string("476")

#define ERR_CHANOPRIVSNEEDED std::string("482")

#define ERR_UMODEUNKNOWNFLAG std::string("501")
#define ERR_USERSDONTMATCH std::string("502")
#define ERR_INVALIDMODEPARAM std::string("696")

#endif