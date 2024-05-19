cmake_minimum_required(VERSION 3.28)
project(assistant)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

set(CMAKE_INSTALL_RPATH "$ORIGIN/lib")

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(ZXing REQUIRED)
find_package(Tesseract REQUIRED)
find_package(facedetection REQUIRED)
find_package(OpenCV COMPONENTS imgcodecs REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        forms/mainwindow.ui
        resources/resource.qrc
        src/ui/MainWindow.cpp
        include/ui/MainWindow.h
        include/core/structures.h
        include/ui/Menu.h
        src/ui/Menu.cpp
        include/ui/MenuItem.h
        src/ui/MenuItem.cpp
        include/ui/TextBar.h
        src/ui/TextBar.cpp
        include/ui/MessageEdit.h
        src/ui/MessageEdit.cpp
        include/ui/MessageLabel.h
        src/ui/MessageLabel.cpp
        include/ui/UsernameLabel.h
        src/ui/UsernameLabel.cpp
        include/ui/ImageLabel.h
        src/ui/ImageLabel.cpp
        include/ui/Slider.h
        src/ui/Slider.cpp
        include/ui/qr/Settings.h
        src/ui/qr/Settings.cpp
        include/ui/Chat.h
        src/ui/Chat.cpp
        include/ui/qr/Area.h
        src/ui/qr/Area.cpp
        include/qr/ZxingCpp.h
        src/qr/ZxingCpp.cpp
        include/ocr/Tesseract.h
        src/ocr/Tesseract.cpp
        include/ocr/QTesseract.h
        src/ocr/QTesseract.cpp
        include/ui/ocr/Area.h
        src/ui/ocr/Area.cpp
        include/ui/UploadBar.h
        src/ui/UploadBar.cpp
        include/ui/ocr/Settings.h
        src/ui/ocr/Settings.cpp
        include/ui/SelectBox.h
        src/ui/SelectBox.cpp
        include/ui/MessageDialog.h
        src/ui/MessageDialog.cpp
        include/utils/ImageIo.h
        src/utils/ImageIo.cpp
        include/utils/DateTime.h
        src/utils/DateTime.cpp
        include/core/app.h
        include/face/Libfacedetection.h
        src/face/Libfacedetection.cpp
        include/face/QLibfacedetection.h
        src/face/QLibfacedetection.cpp
        include/ui/face/Settings.h
        src/ui/face/Settings.cpp
        include/ui/face/Area.h
        src/ui/face/Area.cpp
        include/utils/Visualize.h
        src/utils/Vizualize.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} Qt::Widgets ZXing::ZXing Tesseract::libtesseract facedetection opencv_imgcodecs)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_SOURCE_DIR}/${CMAKE_PREFIX_PATH}")
