FROM debian:stretch-slim

ARG WORKSPACE_DIR

RUN mkdir ${WORKSPACE_DIR}
WORKDIR ${WORKSPACE_DIR}

COPY ./tools/* ./

RUN ./add-sury-repo.sh

ARG PHP_VERSION

RUN apt-get update && apt-get install -y php${PHP_VERSION}-dev g++

COPY ./sources/* ./

RUN phpize && ./configure --enable-multisearch

ENTRYPOINT ["make"]
