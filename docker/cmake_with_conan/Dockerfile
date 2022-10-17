FROM gcc:12

ARG CONAN_VERSION=1.51.0

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="cmake_with_conan"

# install deps (python and cmake)
RUN apt-get update && apt-get install python3-dev python3-pip cmake --no-install-recommends -y && apt-get clean

RUN pip install --no-cache-dir -Iv conan==${CONAN_VERSION}

RUN g++ -v && \
    gcc -v && \
    gcov -v && \
    make -v && \
    cmake --version && \
    conan --version
