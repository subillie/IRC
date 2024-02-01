


# docker make file

all 		:
	docker build . --tag irc:my
	docker run --name irc --rm irc:my

run		:
	docker run --name irc --rm irc:my

local		:
	docker exec -it irc irssi -c host.docker.internal -p 6667 -n one -w 1234
	
c1		:
	docker exec -it irc irssi -c 127.0.0.1 -p 6667

c2		:
	docker exec -it irc irssi -c 127.0.0.1 -p 6667 -n two

c3		:
	docker exec -it irc irssi -c 127.0.0.1 -p 6667 -n three

c4		:
	docker exec -it irc irssi -c 127.0.0.1 -p 6667 -n four

c5		:
	docker exec -it irc irssi -c 127.0.0.1 -p 6667 -n five

n1		:
	docker exec -it irc nc 127.0.0.1 6667

n2		:
	docker exec -it irc nc 127.0.0.1 6667

n3		:
	docker exec -it irc nc 127.0.0.1 -p 6667

n4		:
	docker exec -it irc nc 127.0.0.1 -p 6667

n5		:
	docker exec -it irc nc 127.0.0.1 -p 6667


exec		:
	docker exec -it irc bash

down		:
	docker stop irc

clean		:
	docker system prune -a

re			:
	make clean
	make all

.PHONY		: all run c1 c2 c3 c4 c5 exec down clean re