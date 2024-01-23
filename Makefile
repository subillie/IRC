CC 		=	c++

CFLAGS 	=	-std=c++98 -Wall -Wextra -Werror #-g -fsanitize=address

NAME 	=	ircserv

SRCS	=	Channel/Channel.cpp \
			Client/Client.cpp \
			RequestHandler/RequestHandler.cpp \
			Server/Server.cpp \
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