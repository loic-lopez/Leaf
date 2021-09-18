FROM debian:bookworm-slim as cmake_builder

ARG CMAKE_VERSION=3.21.2

RUN apt-get update && \
    apt-get install --no-install-recommends g++-11 -y && \
    apt-get install --no-install-recommends make libssl-dev -y && \
    apt-get install wget -y && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10 && \
    update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-11 10 && \
    update-alternatives --install /usr/bin/gcov-tool gcov-tool /usr/bin/gcov-tool-11 10 && \
    update-alternatives --install /usr/bin/gcov-dump gcov-dump /usr/bin/gcov-dump-11 10 && \
    update-alternatives --install /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-11 10 && \
    update-alternatives --install /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-11 10 && \
    update-alternatives --install /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-11 10 && \
    g++ -v && \
    gcc -v

WORKDIR /tmp

RUN wget https://github.com/Kitware/CMake/releases/download/v$CMAKE_VERSION/cmake-$CMAKE_VERSION.tar.gz && \
    tar -xzf cmake-$CMAKE_VERSION.tar.gz

RUN cd cmake-$CMAKE_VERSION && \
    ./bootstrap && \
    make -j$(nproc) && \
    make install

FROM debian:bookworm-slim

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/Leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="cmake_with_conan"

RUN echo 'deb http://deb.debian.org/debian experimental main' >> /etc/apt/sources.list

COPY --from=cmake_builder /usr/local /usr/local

RUN apt-get update && \
    apt-get install --no-install-recommends g++-11 -y && \
    apt-get install python3-pip make -y --no-install-recommends && \
    apt-get clean && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10 && \
    update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-11 10 && \
    update-alternatives --install /usr/bin/gcov-tool gcov-tool /usr/bin/gcov-tool-11 10 && \
    update-alternatives --install /usr/bin/gcov-dump gcov-dump /usr/bin/gcov-dump-11 10 && \
    update-alternatives --install /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-11 10 && \
    update-alternatives --install /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-11 10 && \
    update-alternatives --install /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-11 10 && \
    g++ -v && \
    gcc -v && \
    gcov -v

RUN pip install conan