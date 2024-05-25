#!/bin/bash

WORKDIR=$(pwd)

# xorg
git clone https://gitlab.freedesktop.org/xorg/proto/xcbproto.git --depth=1
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
  'libxau'
  'libxdmcp'
  'libx11'
)

for library in "${LIBRARIES[@]}"; do
  cd $WORKDIR
  git clone --recursive https://gitlab.freedesktop.org/xorg/lib/${library}.git --depth=1
  cd $library

  ./autogen.sh
  ./configure
  make -j$(nproc) CFLAGS='-static -fPIC'
  make install
done

# GLib
cd $WORKDIR
git clone https://gitlab.gnome.org/GNOME/glib.git --depth=1 --branch=2.80.2

cd glib
mkdir build && cd build

meson setup .. --buildtype=release --default-library=static --libdir=lib
ninja -j$(nproc)
ninja install

# libxkbcommon
cd $WORKDIR
git clone https://github.com/xkbcommon/libxkbcommon.git --depth=1 --branch=xkbcommon-1.7.0

cd libxkbcommon
mkdir build && cd build

meson setup .. --buildtype=release --default-library=static --libdir=lib -Dx-locale-root=/usr/share/X11/locale \
    -Denable-xkbregistry=false -Denable-tools=false \
    -Dc_link_args="-Wl,--start-group /usr/local/lib/libXau.a /usr/local/lib/libXdmcp.a -Wl,--end-group"
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
sed -i '/^        XCB::XCB/a\        X11::Xdmcp\n        X11::Xau' qtbase/src/gui/configure.cmake
sed -i '/^        XKB::XKB/a\        X11::Xdmcp\n        X11::Xau' qtbase/src/plugins/platforms/xcb/CMakeLists.txt

mkdir build && cd build

../configure -prefix /opt/assistant/deps -ccache -qt-zlib -qt-libjpeg -qt-libpng -qt-pcre -qt-harfbuzz \
    -bundled-xcb-xinput -fontconfig -system-freetype \
    -no-dbus -no-opengl -no-feature-sql -no-feature-xml -no-feature-printsupport -no-feature-concurrent \
    -no-feature-network -no-feature-androiddeployqt -no-feature-qmake
cmake --build . -j$(nproc)
cmake --install . --strip

# zxing-cpp
cd $WORKDIR
git clone https://github.com/zxing-cpp/zxing-cpp.git --depth=1 --branch=v2.2.1

cd zxing-cpp
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DBUILD_EXAMPLES=OFF
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip

# Leptonica
cd $WORKDIR
git clone https://github.com/DanBloomberg/leptonica.git --depth=1 --branch=1.84.1

cd leptonica
sed -i '/include(GNUInstallDirs)/a add_definitions(-DNO_CONSOLE_IO)' CMakeLists.txt

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DENABLE_WEBP=OFF -DENABLE_OPENJPEG=OFF \
  -DENABLE_GIF=OFF -DENABLE_TIFF=OFF -DENABLE_ZLIB=OFF -DENABLE_PNG=OFF -DENABLE_JPEG=OFF
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip
cmake --install . --strip

# Tesseract OCR
cd $WORKDIR
git clone https://github.com/tesseract-ocr/tesseract.git --depth=1 --branch=5.3.4

cd tesseract
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DBUILD_TRAINING_TOOLS=OFF
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip

# libfacedetection
cd $WORKDIR
git clone https://github.com/ShiqiYu/libfacedetection.git --depth=1

cd libfacedetection
sed -i '/ADD_LIBRARY(${fdt_lib_name} ${fdt_source_files} ${INSTALLHEADER_FILES})/a target_link_libraries(${fdt_lib_name} ${OpenMP_gomp_LIBRARY})' CMakeLists.txt

mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DENABLE_AVX2=ON
cmake --build . -j$(nproc)
cmake --install . --prefix /opt/assistant/deps --strip

# OpenCV
cd $WORKDIR
git clone https://github.com/opencv/opencv.git --depth=1 --branch=4.9.0

cd opencv
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_ZLIB=ON -DBUILD_JPEG=ON -DBUILD_PNG=ON -DWITH_TBB=ON -DBUILD_TBB=ON \
  -DBUILD_opencv_apps=OFF -DBUILD_LIST=core,imgcodecs,imgproc,videoio \
  -DCMAKE_INSTALL_PREFIX=/opt/assistant/deps -DCMAKE_INSTALL_RPATH='$ORIGIN'
cmake --build . -j$(nproc)
cmake --install . --strip
