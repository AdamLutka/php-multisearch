FROM debian:stretch-slim

RUN apt-get update \
	&& apt-get install -y wget apt-transport-https ca-certificates \
	&& wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg \
	&& sh -c 'echo "deb https://packages.sury.org/php/ stretch main" > /etc/apt/sources.list.d/php.list' 

RUN apt-get update && apt-get install -y php7.1-dev g++

RUN mkdir /var/workspace
WORKDIR /var/workspace

COPY build/content/* ./

RUN phpize && ./configure --enable-multisearch

CMD ./entrypoint.sh
