#!/bin/sh

apt-get update \
	&& apt-get install -y wget lsb-release apt-transport-https ca-certificates \
	&& wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg \
	&& sh -c 'echo "deb https://packages.sury.org/php/ `lsb_release -cs` main" > /etc/apt/sources.list.d/php.list' 
