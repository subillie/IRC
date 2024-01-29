#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

// TODO: 서버 이름 바꾸기
#define SERVER std::string("IRC")

#define RPL_WELCOME std::string("001")
#define RPL_UMODEIS std::string("221")
#define RPL_AWAY std::string("301")
#define RPL_TOPIC std::string("332")
#define RPL_NAMREPLY std::string("353")
#define RPL_ENDOFNAMES std::string("366")

#endif