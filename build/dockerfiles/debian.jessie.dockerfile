FROM debian:jessie-slim

ARG WORKSPACE_DIR

RUN mkdir ${WORKSPACE_DIR}
WORKDIR ${WORKSPACE_DIR}

COPY ./tools/* ./

RUN ./add-sury-repo.sh

RUN echo 'deb http://ftp.us.debian.org/debian unstable main contrib non-free' > /etc/apt/sources.list.d/unstable.list; \
	echo "Package: *\nPin: release a=unstable\nPin-Priority: 100" > /etc/apt/preferences.d/unstable; \
	apt-get update && apt-get install -y -t unstable g++

ARG PHP_VERSION

RUN apt-get update && apt-get install -y php${PHP_VERSION}-dev

COPY ./sources/* ./

RUN phpize && ./configure --enable-multisearch STATIC_CPP_STD=yes

ENTRYPOINT ["make"]
