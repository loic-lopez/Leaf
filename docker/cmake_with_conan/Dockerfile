FROM debian:bullseye-slim

RUN apt-get update

RUN apt-get install g++ python3-pip wget make libssl-dev -y

WORKDIR /tmp

RUN wget https://github.com/Kitware/CMake/releases/download/v3.20.2/cmake-3.20.2.tar.gz && \
    tar -xzvf cmake-3.20.2.tar.gz

RUN cd cmake-3.20.2 && \
    ./bootstrap && \
    make -j4 && \
    make install

RUN rm -rf /tmp/*

RUN adduser --disabled-password --gecos "" leaf

USER leaf

RUN pip install conan

ENV PATH="$PATH:/home/leaf/.local/bin"

RUN mkdir -p /home/leaf/workspace/build

VOLUME /home/leaf/workspace/leaf

WORKDIR /home/leaf/workspace/