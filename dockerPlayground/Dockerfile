FROM	ubuntu:latest

RUN		apt-get update -y \
		&& apt-get install inspircd irssi tcpflow dumb-init netcat -y

RUN		mkdir -p /var/run/inspircd

COPY	run.sh .

RUN		chmod 777 run.sh

ENTRYPOINT	[ "dumb-init", "--" ]

CMD			[ "./run.sh" ]