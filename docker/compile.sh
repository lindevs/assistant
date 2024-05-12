#!/bin/bash

WORKDIR=$(pwd)

# Qt
git clone https://github.com/qt/qt5.git qt6

cd qt6
git checkout 6.7.1

perl init-repository --module-subset=qtbase

mkdir build && cd build

../configure -prefix /opt/assistant/deps -qt-zlib -qt-libjpeg -qt-libpng -qt-pcre -qt-harfbuzz \
    -bundled-xcb-xinput -fontconfig -system-freetype \
    -no-dbus -no-feature-sql -no-feature-xml -no-feature-printsupport -no-feature-concurrent -no-feature-network
cmake --build . -j$(nproc)
cmake --install . --strip

# zxing-cpp
cd $WORKDIR
git clone https://github.com/zxing-cpp/zxing-cpp.git

cd zxing-cpp
git checkout v2.2.1

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip

# Leptonica
cd $WORKDIR
git clone https://github.com/DanBloomberg/leptonica.git

cd leptonica
git checkout 1.84.1
sed -i '/include(GNUInstallDirs)/a add_definitions(-DNO_CONSOLE_IO)' CMakeLists.txt

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DENABLE_WEBP=OFF -DENABLE_OPENJPEG=OFF \
  -DENABLE_GIF=OFF -DENABLE_TIFF=OFF -DENABLE_ZLIB=OFF -DENABLE_PNG=OFF -DENABLE_JPEG=OFF
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip
cmake --install . --strip

# Tesseract OCR
cd $WORKDIR
git clone https://github.com/tesseract-ocr/tesseract.git

cd tesseract
git checkout 5.3.4

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DBUILD_TRAINING_TOOLS=OFF
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip

# OpenCV
git clone https://github.com/opencv/opencv.git

cd opencv
git checkout 4.9.0

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_ZLIB=ON -DBUILD_JPEG=ON -DBUILD_PNG=ON -DWITH_TBB=ON -DBUILD_TBB=ON \
  -DBUILD_opencv_apps=OFF -DBUILD_LIST=core,imgcodecs,imgproc,videoio \
  -DCMAKE_INSTALL_PREFIX=/opt/assistant/deps -DCMAKE_INSTALL_RPATH='$ORIGIN'
cmake --build . -j$(nproc)
cmake --install . --strip
