#!/bin/bash

WORKDIR=$(pwd)

# xorg
git clone https://gitlab.freedesktop.org/xorg/proto/xcbproto.git
cd xcbproto
./autogen.sh
make install

LIBRARIES=(
  'libxcb'
  'libxcb-render-util'
  'libxcb-wm'
  'libxcb-keysyms'
  'libxcb-util'
  'libxcb-image'
  'libxcb-cursor'
  'libice'
  'libsm'
  'libx11'
)

for library in "${LIBRARIES[@]}"; do
  cd $WORKDIR
  git clone --recursive https://gitlab.freedesktop.org/xorg/lib/${library}.git
  cd $library

  ./autogen.sh
  ./configure
  make -j$(nproc) CFLAGS='-static -fPIC'
  make install
done

rm -rf /usr/local/lib/libxcb.a

# GLib
cd $WORKDIR
git clone https://gitlab.gnome.org/GNOME/glib.git

cd glib
mkdir build && cd build

meson setup .. --default-library static
ninja -j$(nproc)
ninja install

# Qt
cd $WORKDIR
git clone https://github.com/qt/qt5.git qt6

cd qt6
git checkout 6.7.1

perl init-repository --module-subset=qtbase

# https://bugreports.qt.io/browse/QTBUG-86287
sed -i 's/set(XCB_IMAGE_component_deps XCB SHM)/set(XCB_IMAGE_component_deps XCB SHM UTIL)/' qtbase/cmake/3rdparty/extra-cmake-modules/find-modules/FindXCB.cmake
sed -i '/^    IMAGE/d' qtbase/cmake/3rdparty/extra-cmake-modules/find-modules/FindXCB.cmake
sed -i '/^    UTIL/a\    IMAGE' qtbase/cmake/3rdparty/extra-cmake-modules/find-modules/FindXCB.cmake

mkdir build && cd build

../configure -prefix /opt/assistant/deps -ccache -qt-zlib -qt-libjpeg -qt-libpng -qt-pcre -qt-harfbuzz \
    -bundled-xcb-xinput -fontconfig -system-freetype \
    -no-dbus -no-opengl -no-feature-sql -no-feature-xml -no-feature-printsupport -no-feature-concurrent \
    -no-feature-network -no-feature-androiddeployqt -no-feature-qmake
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
