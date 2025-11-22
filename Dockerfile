FROM debian:buster-slim

# Corrige os repositórios apontando para o Archive
RUN sed -i 's|deb.debian.org/debian|archive.debian.org/debian|g' /etc/apt/sources.list && \
    sed -i 's|deb.debian.org/debian-security|archive.debian.org/debian-security|g' /etc/apt/sources.list && \
    echo 'Acquire::Check-Valid-Until "false";' > /etc/apt/apt.conf.d/99no-check-valid && \
    apt-get update && \
    apt-get -y upgrade && \
    apt-get install -y git build-essential clang valgrind && \
    mkdir -m 777 /project

WORKDIR /project
