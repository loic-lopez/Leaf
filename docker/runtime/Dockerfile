FROM ghcr.io/loic-lopez/cmake_with_conan:latest as leaf_builder

ARG BUILD_WORKDIR=/build
ARG TARGET_INSTALL_DIR=/leaf

RUN mkdir -p $BUILD_WORKDIR/leaf

ADD debian $BUILD_WORKDIR/leaf

RUN mkdir -p $BUILD_WORKDIR/build

WORKDIR $BUILD_WORKDIR/build

RUN cmake -DCMAKE_BUILD_TYPE=Release -DLEAF_ROOT_PATH=$TARGET_INSTALL_DIR ../leaf
RUN make -j && ctest -V
RUN cmake --install . --prefix $TARGET_INSTALL_DIR --config Release

RUN rm -rf $TARGET_INSTALL_DIR/*.log


FROM debian:stable-slim

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="leaf"

ARG TARGET_INSTALL_DIR=/leaf

RUN groupadd -r leaf && useradd --no-log-init --create-home -r -g leaf leaf
COPY --chown=leaf:leaf --from=leaf_builder $TARGET_INSTALL_DIR $TARGET_INSTALL_DIR
RUN mkdir -p ${TARGET_INSTALL_DIR}/log && chown -R leaf:leaf ${TARGET_INSTALL_DIR}

RUN echo 'deb http://deb.debian.org/debian testing main contrib non-free' >> /etc/apt/sources.list
RUN apt-get update && apt-get upgrade -y && apt-get dist-upgrade -y && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /opt/leaf
ADD docker/runtime/docker_start_leaf.sh /opt/leaf
RUN chmod 755 /opt/leaf/docker_start_leaf.sh && chown leaf:leaf /opt/leaf/docker_start_leaf.sh

USER leaf

WORKDIR $TARGET_INSTALL_DIR
ENV LEAF_INSTALL_DIR=$TARGET_INSTALL_DIR

ENTRYPOINT exec ${LEAF_INSTALL_DIR}/bin/leaf --server-config-file ${LEAF_INSTALL_DIR}/conf/leaf.ini