FROM ubuntu:22.04

WORKDIR /opt/assistant

COPY compile.sh compile.sh

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
        curl ca-certificates git build-essential ninja-build ccache \
        autoconf automake xutils-dev libtool gperf python3-pip \
        libicu-dev libsdl2-dev xorg-dev libx11-xcb-dev libxkbcommon-x11-dev \
    && pip3 install meson packaging \
    && curl -sSo /etc/apt/trusted.gpg.d/kitware-key.asc https://apt.kitware.com/keys/kitware-archive-latest.asc \
    && echo "deb https://apt.kitware.com/ubuntu/ jammy main" > /etc/apt/sources.list.d/kitware.list \
    && apt update \
    && apt install -y cmake \
    && rm -rf /var/lib/apt/lists/*

ENTRYPOINT ["/bin/bash"]
