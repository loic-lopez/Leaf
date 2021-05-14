FROM debian:bullseye-slim as sonar_cloud_scanner_builder

ARG SONAR_SCANNER_VERSION=4.6.2.2472

RUN mkdir /tools/

WORKDIR /tools

RUN apt-get update && apt-get install wget unzip -y

RUN wget https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-$SONAR_SCANNER_VERSION-linux.zip \
    && unzip sonar-scanner-cli-$SONAR_SCANNER_VERSION-linux.zip \
    && mv sonar-scanner-$SONAR_SCANNER_VERSION-linux sonar-scanner-cli

RUN wget https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip \
    && unzip build-wrapper-linux-x86.zip

RUN rm *.zip

FROM ghcr.io/loic-lopez/cmake_with_conan:v0.1.33

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/Leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="sonar_cloud_scanner"

RUN mkdir -p /home/leaf/bin/build-wrapper-linux-x86
RUN mkdir -p /home/leaf/bin/sonar-scanner-cli

COPY --from=sonar_cloud_scanner_builder /tools/build-wrapper-linux-x86 /home/leaf/bin/build-wrapper-linux-x86

COPY --from=sonar_cloud_scanner_builder /tools/sonar-scanner-cli /home/leaf/bin/sonar-scanner-cli

ENV PATH=$PATH:/home/leaf/bin/build-wrapper-linux-x86

ENV PATH=$PATH:/home/leaf/bin/sonar-scanner-cli/bin