FROM debian:bullseye-slim as cmake_builder

ARG CMAKE_VERSION=3.21.2

RUN echo 'deb http://deb.debian.org/debian experimental main' >> /etc/apt/sources.list

RUN apt-get update && \
    apt-get -t experimental install --no-install-recommends g++ -y && \
    apt-get install --no-install-recommends make libssl-dev -y && \
    apt-get install wget -y

WORKDIR /tmp

RUN wget https://github.com/Kitware/CMake/releases/download/v$CMAKE_VERSION/cmake-$CMAKE_VERSION.tar.gz && \
    tar -xzf cmake-$CMAKE_VERSION.tar.gz

RUN cd cmake-$CMAKE_VERSION && \
    ./bootstrap && \
    make -j$(nproc) && \
    make install

FROM debian:bullseye-slim

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/Leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="cmake_with_conan"

RUN echo 'deb http://deb.debian.org/debian experimental main' >> /etc/apt/sources.list

COPY --from=cmake_builder /usr/local /usr/local

RUN apt-get update && \
    apt-get -t experimental install --no-install-recommends g++ -y && \
    apt-get install python3-pip make -y --no-install-recommends && \
    apt-get clean

RUN pip install conan