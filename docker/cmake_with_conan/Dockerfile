FROM debian:bullseye-slim as cmake_builder

RUN apt-get update && apt-get install g++ wget make libssl-dev -y

WORKDIR /tmp

RUN wget https://github.com/Kitware/CMake/releases/download/v3.20.2/cmake-3.20.2.tar.gz && \
    tar -xzf cmake-3.20.2.tar.gz

RUN cd cmake-3.20.2 && \
    ./bootstrap && \
    make -j4 && \
    make install

RUN rm -rf /tmp/*

FROM debian:bullseye-slim

COPY --from=cmake_builder /usr/local /usr/local

RUN apt-get update && apt-get install g++ python3-pip make -y

RUN adduser --disabled-password --gecos "" leaf

USER leaf

ENV PATH="$PATH:/home/leaf/.local/bin"

RUN pip install conan

RUN mkdir -p /home/leaf/workspace/build

VOLUME /home/leaf/workspace/leaf

WORKDIR /home/leaf/workspace/