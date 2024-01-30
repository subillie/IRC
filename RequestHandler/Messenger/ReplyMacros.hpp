#ifndef REPLYMACROS_HPP
#define REPLYMACROS_HPP

#include <string>

#define SERVER std::string("IRC")
#define VERSION std::string("1.0")
#define AVAILABLE_USER_MODES std::string("i")
#define AVAILABLE_CHAN_MODES std::string("klit")
// 인자 확인
#define ISUPPORT_PARAMS                                                   \
  std::string(                                                            \
      "CASEMAPPING=ascii CHANLIMIT=#:10 CHANMODES=,k,l,it CHANNELLEN=32 " \
      "CHANTYPES=# KICKLEN=307 NICKLEN=31 PREFIX=(o)@ TOPICLEN=307 "      \
      "USERLEN=12")
#define RPL_WELCOME std::string("001")
#define RPL_YOURHOST std::string("002")
#define RPL_CREATED std::string("003")
#define RPL_MYINFO std::string("004")
#define RPL_ISUPPORT std::string("005")
#define RPL_UMODEIS std::string("221")
#define RPL_AWAY std::string("301")
#define RPL_CHANNELMODEIS std::string("324")
#define RPL_TOPIC std::string("332")
#define RPL_INVITELIST std::string("336")
#define RPL_INVITING std::string("341")
#define RPL_NAMREPLY std::string("353")
#define RPL_ENDOFNAMES std::string("366")

#endif
