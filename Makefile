CC 		=	c++

CFLAGS 	=	-std=c++98 -Wall -Wextra -Werror -g -fsanitize=address

NAME 	=	ircserv

SRCS	=	Channel/Channel.cpp \
			Client/Client.cpp \
			RequestHandler/RequestHandler.cpp \
			RequestHandler/Messenger/Messenger.cpp \
			RequestHandler/Messenger/Errors.cpp \
			RequestHandler/Messenger/Replies.cpp \
			RequestHandler/Commands/Cap.cpp \
			RequestHandler/Commands/Invite.cpp \
			RequestHandler/Commands/Join.cpp \
			RequestHandler/Commands/Kick.cpp \
			RequestHandler/Commands/Mode.cpp \
			RequestHandler/Commands/Nick.cpp \
			RequestHandler/Commands/Part.cpp \
			RequestHandler/Commands/Pass.cpp \
			RequestHandler/Commands/Pong.cpp \
			RequestHandler/Commands/Privmsg.cpp \
			RequestHandler/Commands/Topic.cpp \
			RequestHandler/Commands/User.cpp \
			Server/Server.cpp \
			Server/Wrappers.cpp \
			Print/Print.cpp \
			main.cpp

OBJS 	=	$(SRCS:%.cpp=%.o)

%.o		:	%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : 
		make fclean 
		make all

.PHONY: all clean fclean re