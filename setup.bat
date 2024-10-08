@echo off
setlocal

set "arg1=%1"

if /i "%arg1%" neq "build-deps" if /i "%arg1%" neq "build-assistant" if /i "%arg1%" neq "test-assistant" if /i "%arg1%" neq "build-archive" (
  echo Available arguments: build-deps, test-assistant, build-assistant
  exit /b 1
)

if /i "%arg1%" == "build-deps" (
  call scripts/compile.bat

  exit /b 0
)

if /i "%arg1%" == "build-assistant" (
  if exist build rmdir /s /q build
  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=deps
  cmake --build build -j%NUMBER_OF_PROCESSORS%
  cmake --install build

  exit /b 0
)

if /i "%arg1%" == "test-assistant" (
  if exist build rmdir /s /q build
  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=deps -DBUILD_TESTING=ON
  cmake --build build --target assistant_tests -j%NUMBER_OF_PROCESSORS%
  .\build\tests\assistant_tests

  exit /b 0
)

if /i "%arg1%" == "build-archive" (
  cd build && tar czf lindevs-assistant.tar.gz app

  exit /b 0
)
