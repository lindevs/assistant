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
  make -j$(nproc) CFLAGS='-static -fPIC'
  make install
done

# GLib
cd $WORKDIR
git clone https://gitlab.gnome.org/GNOME/glib.git --depth=1 --branch=2.80.2

cd glib
mkdir build && cd build

meson setup .. --buildtype=release --default-library=static --libdir=lib -Dtests=false
ninja -j$(nproc)
ninja install

# libxkbcommon
cd $WORKDIR
git clone https://github.com/xkbcommon/libxkbcommon.git --depth=1 --branch=xkbcommon-1.7.0

cd libxkbcommon
mkdir build && cd build

meson setup .. --buildtype=release --default-library=static --libdir=lib --datadir=/usr/share \
    -Denable-xkbregistry=false -Denable-tools=false \
    -Dc_link_args="-Wl,--start-group /usr/local/lib/libXau.a /usr/local/lib/libXdmcp.a -Wl,--end-group"
ninja -j$(nproc)
ninja install

# zlib
cd $WORKDIR
git clone https://github.com/madler/zlib.git --depth=1 --branch=v1.3.1

cd zlib
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DZLIB_BUILD_EXAMPLES=OFF
cmake --build . -j$(nproc)
cmake --install . --strip
rm -rf /usr/local/lib/libz.so*

# libpng
cd $WORKDIR
git clone https://github.com/pnggroup/libpng.git --depth=1 --branch=v1.6.43

cd libpng
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DPNG_SHARED=OFF -DPNG_TESTS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON
cmake --build . -j$(nproc)
cmake --install . --strip

# FreeType
cd $WORKDIR
git clone https://github.com/freetype/freetype.git --depth=1 --branch=VER-2-13-2

cd freetype
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DFT_DISABLE_HARFBUZZ=ON -DFT_DISABLE_BZIP2=ON -DFT_DISABLE_BROTLI=ON
cmake --build . -j$(nproc)
cmake --install . --strip

# Expat
cd $WORKDIR
git clone https://github.com/libexpat/libexpat.git --depth=1 --branch=R_2_6_2

cd libexpat/expat
mkdir build && cd build

cmake -S ../ -B . -G Ninja -DBUILD_SHARED_LIBS=OFF -DEXPAT_BUILD_EXAMPLES=OFF -DEXPAT_BUILD_TESTS=OFF \
    -DEXPAT_BUILD_TOOLS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON
cmake --build . -j$(nproc)
cmake --install . --strip

# Fontconfig
cd $WORKDIR
git clone https://gitlab.freedesktop.org/fontconfig/fontconfig.git --depth=1 --branch=2.15.0

cd fontconfig
mkdir build && cd build

meson setup .. --buildtype=release --default-library=static --libdir=lib --sysconfdir=/etc --datadir=/usr/share \
    --localstatedir=/var -Dtests=disabled -Dtools=disabled
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
sed -i '/QMAKE_LIB fontconfig)/a\qt_find_package(EXPAT PROVIDED_TARGETS EXPAT::EXPAT MODULE_NAME gui QMAKE_LIB expat)' qtbase/src/gui/configure.cmake
sed -i '/^        Fontconfig::Fontconfig/a\        EXPAT::EXPAT' qtbase/src/gui/CMakeLists.txt

mkdir build && cd build

../configure -prefix /opt/assistant/deps -ccache -qt-pcre -qt-harfbuzz \
    -bundled-xcb-xinput -fontconfig -system-freetype \
    -no-ico -no-libjpeg -no-gif -no-dbus -no-linuxfb -no-opengl -no-evdev -no-feature-sql -no-feature-xml \
    -no-feature-printsupport -no-feature-concurrent -no-feature-network -no-feature-androiddeployqt -no-feature-qmake
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
