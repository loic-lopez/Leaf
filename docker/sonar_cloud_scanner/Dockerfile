FROM debian:stable-slim as sonar_cloud_scanner_builder

ARG SONAR_SCANNER_VERSION=4.7.0.2747

RUN mkdir /tools/

WORKDIR /tools

RUN apt-get update && apt-get install wget unzip ca-certificates --no-install-recommends -y

RUN wget https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-$SONAR_SCANNER_VERSION-linux.zip \
    && unzip sonar-scanner-cli-$SONAR_SCANNER_VERSION-linux.zip \
    && mv sonar-scanner-$SONAR_SCANNER_VERSION-linux sonar-scanner-cli

RUN wget https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip \
    && unzip build-wrapper-linux-x86.zip

RUN rm *.zip

FROM ghcr.io/loic-lopez/cmake_with_conan:v0.1.53

LABEL org.opencontainers.image.source="https://github.com/loic-lopez/Leaf"
LABEL org.opencontainers.image.authors="Loïc LOPEZ"
LABEL org.opencontainers.image.title="sonar_cloud_scanner"

RUN apt-get update && apt-get install git --no-install-recommends -y && apt-get clean

RUN pip install gcovr==5.0 --no-cache-dir && gcovr --version

RUN mkdir -p /sonar/build-wrapper-linux-x86
RUN mkdir -p /sonar/sonar-scanner-cli
RUN mkdir -p /sonar/bin

COPY --from=sonar_cloud_scanner_builder /tools/build-wrapper-linux-x86 /sonar/build-wrapper-linux-x86

COPY --from=sonar_cloud_scanner_builder /tools/sonar-scanner-cli /sonar/sonar-scanner-cli

COPY ./scripts/sonar_test_report_converter.py /sonar/bin/sonar_test_report_converter

RUN chmod +x /sonar/bin/sonar_test_report_converter

ENV PATH=$PATH:/sonar/build-wrapper-linux-x86:/sonar/sonar-scanner-cli/bin:/sonar/bin
