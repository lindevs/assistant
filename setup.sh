#!/bin/bash

if [[ ! $1 =~ ^(build-image|build-deps|build-assistant|test-assistant|build-archive)$ ]]; then
  echo 'Available arguments: build-image, build-deps, build-assistant, test-assistant, build-archive'
  exit 1
fi

if [[ $1 == build-image ]]; then
  BACKEND=cpu
  [[ $2 == cuda ]] && BACKEND=cuda

  cd scripts && docker build --build-arg IMAGE=${BACKEND} -t lindevs-assistant .

  exit 0
fi

if [[ $1 == build-deps ]]; then
  BACKEND=cpu
  [[ $2 == cuda ]] && BACKEND=cuda

  docker run -it --rm -v ./scripts/compile.sh:/opt/assistant/compile.sh -v ./deps:/opt/assistant/deps lindevs-assistant compile.sh ${BACKEND}
  sudo chown -R $USER:$USER ./deps

  exit 0
fi

if [[ $1 == build-assistant ]]; then
  CUDA=OFF
  [[ $2 == cuda ]] && CUDA=ON

  rm -rf build
  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=deps -DUSE_CUDA=${CUDA}
  cmake --build build -j$(nproc)
  cmake --install build --strip

  exit 0
fi

if [[ $1 == test-assistant ]]; then
  rm -rf build
  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=deps -DBUILD_TESTING=ON
  cmake --build build --target assistant_tests -j$(nproc)
  ./build/tests/assistant_tests

  exit 0
fi

if [[ $1 == build-archive ]]; then
  cd build && tar czf lindevs-assistant.tar.gz app

  exit 0
fi
