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

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_BINARY_DIR}/app")

if (WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)

    message(STATUS ${MSVC_RUNTIME_LIBRARY})

    get_filename_component(COMPILER_DIR ${CMAKE_C_COMPILER} DIRECTORY)
    if (EXISTS "${COMPILER_DIR}/msvcp140.dll")
        install(FILES "${COMPILER_DIR}/msvcp140.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    endif ()
    if (EXISTS "${COMPILER_DIR}/vcruntime140.dll")
        install(FILES "${COMPILER_DIR}/vcruntime140.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    endif ()

    install(FILES "${CMAKE_PREFIX_PATH}/bin/Qt6Core.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/Qt6Gui.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/Qt6Widgets.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/plugins/platforms/qwindows.dll" DESTINATION "${CMAKE_BINARY_DIR}/app/platforms")
    install(FILES "${CMAKE_PREFIX_PATH}/plugins/styles/qmodernwindowsstyle.dll" DESTINATION "${CMAKE_BINARY_DIR}/app/styles")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/opencv_core4100.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/opencv_imgproc4100.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/opencv_imgcodecs4100.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/tbb12.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/openblas.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
else ()
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6Core.so.6.7.2" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6Core.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6Gui.so.6.7.2" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6Gui.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6Widgets.so.6.7.2" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6Widgets.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6XcbQpa.so.6.7.2" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6XcbQpa.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/plugins/platforms/libqxcb.so" DESTINATION "${CMAKE_BINARY_DIR}/app/plugins/platforms")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libopencv_core.so.4.10.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libopencv_core.so.410")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libopencv_imgproc.so.4.10.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libopencv_imgproc.so.410")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libopencv_imgcodecs.so.4.10.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libopencv_imgcodecs.so.410")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libtbb.so.12.12" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libtbb.so.12")
endif ()
