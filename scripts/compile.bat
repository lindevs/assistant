@echo off
setlocal

if exist downloads rmdir /s /q downloads
mkdir downloads && cd downloads

set CUDA=OFF
if "%1" == "cuda" set CUDA=ON

set WORKDIR=%CD%

:: Qt
cd %WORKDIR%
git clone https://github.com/qt/qt5.git qt6

cd qt6
git checkout 6.9.1

git submodule update --init qtbase

mkdir build && cd build

call ..\configure -prefix ../../../deps -release -qt-harfbuzz -no-ico -no-libjpeg -no-gif -no-dbus -no-opengl^
    -no-feature-sql -no-feature-xml -no-feature-printsupport -no-feature-concurrent -no-feature-network^
    -no-feature-androiddeployqt -no-feature-windeployqt -no-feature-qmake
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: zxing-cpp
cd %WORKDIR%
git clone https://github.com/zxing-cpp/zxing-cpp.git --depth=1 --branch=v2.3.0

cd zxing-cpp
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF^
    -DCMAKE_INSTALL_PREFIX=../../../deps
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: Leptonica
cd %WORKDIR%
git clone https://github.com/DanBloomberg/leptonica.git --depth=1 --branch=1.85.0

cd leptonica
powershell -command "(gc CMakeLists.txt) -replace 'include\(GNUInstallDirs\)', ('$&' + [Environment]::NewLine + 'add_definitions(-DNO_CONSOLE_IO)') | sc CMakeLists.txt"

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DENABLE_WEBP=OFF -DENABLE_OPENJPEG=OFF^
    -DENABLE_GIF=OFF -DENABLE_TIFF=OFF -DENABLE_ZLIB=OFF -DENABLE_PNG=OFF -DENABLE_JPEG=OFF -DSW_BUILD=OFF^
    -DCMAKE_INSTALL_PREFIX=../../../deps
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: Tesseract OCR
cd %WORKDIR%
git clone https://github.com/tesseract-ocr/tesseract.git --depth=1 --branch=5.5.1

cd tesseract
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DBUILD_TRAINING_TOOLS=OFF -DSW_BUILD=OFF^
    -DCMAKE_INSTALL_PREFIX=../../../deps
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: libfacedetection
cd %WORKDIR%
git clone https://github.com/ShiqiYu/libfacedetection.git --depth=1

cd libfacedetection
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DENABLE_AVX2=ON^
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_INSTALL_PREFIX=../../../deps
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: OpenBLAS
cd %WORKDIR%
git clone https://github.com/OpenMathLib/OpenBLAS.git --depth=1 --branch=v0.3.30

cd OpenBLAS
powershell -command "(gc CMakeLists.txt) -replace 'set\(CMAKE_INSTALL_INCLUDEDIR \${CMAKE_INSTALL_INCLUDEDIR}/openblas\${SUFFIX64}\)', '' | sc CMakeLists.txt"

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_STATIC_LIBS=OFF -DBUILD_SHARED_LIBS=ON^
    -DCMAKE_INSTALL_PREFIX=../../../deps
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: oneTBB
cd %WORKDIR%
git clone https://github.com/oneapi-src/oneTBB.git --depth=1 --branch=v2022.2.0

cd oneTBB
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DTBB_TEST=OFF -DTBBMALLOC_BUILD=OFF^
    -DCMAKE_INSTALL_PREFIX=../../../deps
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: OpenCV
cd %WORKDIR%
git clone https://github.com/opencv/opencv.git --depth=1 --branch=4.12.0

cd opencv
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_ZLIB=ON -DBUILD_JPEG=ON -DBUILD_PNG=ON -DWITH_TBB=ON^
    -DWITH_LAPACK=ON -DWITH_ZLIB_NG=ON -DWITH_FFMPEG=OFF -DWITH_WIN32UI=OFF -DBUILD_opencv_apps=OFF^
    -DBUILD_LIST=core,imgcodecs,imgproc,videoio -DOPENCV_GENERATE_SETUPVARS=OFF -DOPENCV_SKIP_CMAKE_ROOT_CONFIG=ON^
    -DOPENCV_INSTALL_BINARIES_PREFIX= -DOPENCV_CONFIG_INSTALL_PATH=lib/cmake/opencv4 -DCMAKE_INSTALL_PREFIX=../../../deps
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: cuDNN
if "%CUDA%" == "ON" (
  cd %WORKDIR%
  curl -o cudnn.zip https://developer.download.nvidia.com/compute/cudnn/redist/cudnn/windows-x86_64/cudnn-windows-x86_64-9.6.0.74_cuda12-archive.zip

  mkdir cudnn
  tar xf cudnn.zip --strip-components=1 -C cudnn
  set CUDNN_PATH=%WORKDIR%\cudnn

  copy "%CUDNN_PATH%\bin\cudnn64_9.dll" "..\deps\bin" /y >NUL
  copy "%CUDNN_PATH%\bin\cudnn_graph64_9.dll" "..\deps\bin" /y >NUL
  copy "%CUDNN_PATH%\bin\cudnn_ops64_9.dll" "..\deps\bin" /y >NUL
  copy "%CUDNN_PATH%\bin\cudnn_engines_precompiled64_9.dll" "..\deps\bin" /y >NUL
  copy "%CUDNN_PATH%\bin\cudnn_engines_runtime_compiled64_9.dll" "..\deps\bin" /y >NUL
  copy "%CUDNN_PATH%\bin\cudnn_heuristic64_9.dll" "..\deps\bin" /y >NUL
)

:: ONNX Runtime
cd %WORKDIR%

git clone https://github.com/microsoft/onnxruntime.git --depth=1 --branch=v1.22.1

cd onnxruntime/cmake
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -Donnxruntime_BUILD_UNIT_TESTS=OFF -Donnxruntime_BUILD_SHARED_LIB=ON^
    -Donnxruntime_ENABLE_LTO=ON -DONNX_USE_MSVC_STATIC_RUNTIME=ON -Dprotobuf_MSVC_STATIC_RUNTIME=ON^
    -DABSL_MSVC_STATIC_RUNTIME=ON -DCMAKE_MSVC_RUNTIME_LIBRARY="MultiThreaded" -DCMAKE_INSTALL_PREFIX=../../../../deps^
    -Donnxruntime_USE_CUDA=%CUDA%
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .

:: stable-diffusion.cpp
cd %WORKDIR%
git clone --recursive https://github.com/leejet/stable-diffusion.cpp.git --depth=1 --branch=master-d9b5942

cd stable-diffusion.cpp
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DCMAKE_BUILD_TYPE=Release -DSD_BUILD_EXAMPLES=OFF -DSD_BUILD_SHARED_LIBS=ON^
    -DCMAKE_CUDA_ARCHITECTURES="80;86;89" -DCMAKE_INSTALL_PREFIX=../../../deps -DSD_CUDA=%CUDA%
cmake --build . -j%NUMBER_OF_PROCESSORS%
cmake --install .
copy "bin\stable-diffusion.dll" "..\..\..\deps\bin" /y >NUL
copy "stable-diffusion.lib" "..\..\..\deps\lib" /y >NUL
copy "..\stable-diffusion.h" "..\..\..\deps\include" /y >NUL

cd %WORKDIR%/..
rmdir /s /q downloads
