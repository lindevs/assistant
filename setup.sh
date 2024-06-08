#!/bin/bash

if [[ ! $1 =~ ^(build-image|build-deps|build-assistant|build-archive)$ ]]; then
  echo 'Available arguments: build-image, build-deps, build-assistant, build-archive'
  exit 1
fi

if [[ $1 == build-image ]]; then
  cd scripts && docker build -t lindevs-assistant .

  exit 0
fi

if [[ $1 == build-deps ]]; then
  docker run -it --rm -v ./deps:/opt/assistant/deps lindevs-assistant compile.sh

  exit 0
fi

if [[ $1 == build-assistant ]]; then
  rm -rf build
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=deps
  cmake --build build -j$(nproc)
  cmake --install build --strip

  exit 0
fi

if [[ $1 == build-archive ]]; then
  cd build && tar czf lindevs-assistant.tar.gz app

  exit 0
fi
