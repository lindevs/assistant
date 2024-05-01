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

cmake -S ../ -B . -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip
