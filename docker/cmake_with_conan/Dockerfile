FROM debian:stable-slim

ARG CONAN_VERSION=1.51.0

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="cmake_with_conan"

RUN apt-get update

# install python
RUN apt-get install python3-dev python3-pip --no-install-recommends -y

RUN pip install --no-cache-dir -Iv conan==${CONAN_VERSION}

RUN echo 'deb http://deb.debian.org/debian testing main contrib non-free' >> /etc/apt/sources.list

RUN apt-get update && apt-get install build-essential make cmake -y --no-install-recommends

RUN apt-get remove -y gcc-11* g++-11*

RUN apt-get install -y g++-12 gcc-12 --no-install-recommends && apt-get autoremove -y

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 12 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 12 && \
    update-alternatives --install /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-12 12 && \
    update-alternatives --install /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-12 12 && \
    update-alternatives --install /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-12 12 && \
    update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-12 12 && \
    update-alternatives --install /usr/bin/gcov-dump gcov-dump /usr/bin/gcov-dump-12 12 && \
    update-alternatives --install /usr/bin/gcov-tool gcov-tool /usr/bin/gcov-tool-12 12

RUN apt-get clean

RUN g++ -v && \
    gcc -v && \
    gcov -v && \
    make -v && \
    cmake --version && \
    conan --version