#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

// TODO: 서버 이름, 버전, 사용자 모드, 채널 모드 바꾸기
#define SERVER std::string("IRC")
#define VERSION std::string("1.0")
#define AVAILABLE_USER_MODES std::string("i")
#define AVAILABLE_CHAN_MODES std::string("itkl")

#define RPL_WELCOME std::string("001")
#define RPL_YOURHOST std::string("002")
#define RPL_CREATED std::string("003")
#define RPL_MYINFO std::string("004")
#define RPL_AWAY std::string("301")
#define RPL_TOPIC std::string("332")
#define RPL_INVITELIST std::string("336")
#define RPL_NAMREPLY std::string("353")
#define RPL_ENDOFNAMES std::string("366")

#endif