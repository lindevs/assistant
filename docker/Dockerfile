FROM ubuntu:22.04

WORKDIR /opt/assistant

COPY compile.sh compile.sh

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
        curl ca-certificates git build-essential ninja-build ccache \
        autoconf automake pkg-config xutils-dev xtrans-dev libtool gperf bison wayland-protocols python3-pip \
    && pip3 install meson packaging \
    && curl -sSo /etc/apt/trusted.gpg.d/kitware-key.asc https://apt.kitware.com/keys/kitware-archive-latest.asc \
    && echo "deb https://apt.kitware.com/ubuntu/ jammy main" > /etc/apt/sources.list.d/kitware.list \
    && apt update \
    && apt install -y cmake \
    && rm -rf /var/lib/apt/lists/*

ENTRYPOINT ["/bin/bash"]
