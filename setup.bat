@echo off
setlocal

set CUDA=OFF
if "%2" == "cuda" set CUDA=ON

if /i "%1" neq "build-deps" if /i "%1" neq "build-assistant" if /i "%1" neq "test-assistant" if /i "%1" neq "build-archive" (
  echo Available arguments: build-deps, test-assistant, build-assistant
  exit /b 1
)

if /i "%1" == "build-deps" (
  call scripts/compile.bat %2%

  exit /b 0
)

if /i "%1" == "build-assistant" (
  if exist build rmdir /s /q build
  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=deps -DUSE_CUDA=%CUDA%
  cmake --build build -j%NUMBER_OF_PROCESSORS%
  cmake --install build

  exit /b 0
)

if /i "%1" == "test-assistant" (
  if exist build rmdir /s /q build
  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=deps -DBUILD_TESTING=ON
  cmake --build build --target assistant_tests -j%NUMBER_OF_PROCESSORS%
  .\build\tests\assistant_tests

  exit /b 0
)

if /i "%1" == "build-archive" (
  cd build && tar czf lindevs-assistant.tar.gz app

  exit /b 0
)
