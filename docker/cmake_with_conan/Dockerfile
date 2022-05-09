FROM debian:stable-slim

ARG CONAN_VERSION=1.48.0

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="cmake_with_conan"

RUN apt-get update

# install python
RUN apt-get install python3-dev python3-pip --no-install-recommends -y

RUN pip install --no-cache-dir -Iv conan==${CONAN_VERSION}

RUN echo 'deb http://deb.debian.org/debian testing main contrib non-free' >> /etc/apt/sources.list

RUN apt-get update && apt-get install build-essential make cmake -y --no-install-recommends

RUN apt-get clean

RUN g++ -v && \
    gcc -v && \
    gcov -v && \
    make -v && \
    cmake --version && \
    conan --version