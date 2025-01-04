cmake_minimum_required(VERSION 3.28)
project(assistant)

option(BUILD_TESTING "Build tests" OFF)
option(USE_CUDA "Build with CUDA support" OFF)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

set(CMAKE_INSTALL_RPATH "$ORIGIN/lib")

find_package(Qt6 COMPONENTS Widgets REQUIRED QUIET)
find_package(ZXing REQUIRED)
find_package(Tesseract REQUIRED)
find_package(facedetection REQUIRED)
find_package(OpenCV COMPONENTS imgcodecs REQUIRED QUIET)
find_package(onnxruntime REQUIRED)

include(cmake/StableDiffusionConfig.cmake)

set(PROJECT_SOURCES
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
        include/utils/ImgIo.h
        src/utils/ImgIo.cpp
        include/utils/DateTime.h
        src/utils/DateTime.cpp
        include/core/app.h
        include/models/Libfacedetection.h
        src/models/Libfacedetection.cpp
        include/face/QFaceDetection.h
        src/face/QFaceDetection.cpp
        include/ui/face/Settings.h
        src/ui/face/Settings.cpp
        include/ui/face/Area.h
        src/ui/face/Area.cpp
        include/utils/Visualize.h
        src/utils/Vizualize.cpp
        include/models/OrtModel.h
        src/models/OrtModel.cpp
        include/models/Yolov8FaceLindevs.h
        src/models/Yolov8FaceLindevs.cpp
        include/models/UltraFace.h
        src/models/UltraFace.cpp
        include/utils/ImgProc.h
        src/utils/ImgProc.cpp
        include/models/FaceDetectionModel.h
        include/core/models.h
        include/utils/ImgResize.h
        src/utils/ImgResize.cpp
        include/hash/AverageHash.h
        src/hash/AverageHash.cpp
        include/hash/DifferenceHash.h
        src/hash/DifferenceHash.cpp
        include/hash/PerceptualHash.h
        src/hash/PerceptualHash.cpp
        include/hash/WaveletHash.h
        src/hash/WaveletHash.cpp
        include/ui/hash/Settings.h
        src/ui/hash/Settings.cpp
        include/ui/hash/Area.h
        src/ui/hash/Area.cpp
        include/hash/HashAlgorithm.h
        include/core/algorithms.h
        include/hash/QHashCalculation.h
        src/hash/QHashCalculation.cpp
        include/models/DeduplicationModel.h
        include/models/MobileNetV3Dedup.h
        src/models/MobileNetV3Dedup.cpp
        include/ui/dedup/Settings.h
        src/ui/dedup/Settings.cpp
        include/ui/dedup/Area.h
        src/ui/dedup/Area.cpp
        include/dedup/ImageDeduplication.h
        src/dedup/ImageDeduplication.cpp
        include/dedup/QImageDeduplication.h
        src/dedup/QImageDeduplication.cpp
        include/utils/Formatting.h
        src/utils/Formatting.cpp
        include/models/YoloFaceV2.h
        src/models/YoloFaceV2.cpp
        include/models/Yolov5Face.h
        src/models/Yolov5Face.cpp
        include/models/RetinaFace.h
        src/models/RetinaFace.cpp
        include/models/BackgroundMattingModel.h
        include/models/ModNet.h
        src/models/ModNet.cpp
        include/face/QBackgroundMatting.h
        src/face/QBackgroundMatting.cpp
        include/face/IdPhotoCreator.h
        src/face/IdPhotoCreator.cpp
        include/ui/Line.h
        src/ui/Line.cpp
        include/ui/ModelDialog.h
        src/ui/ModelDialog.cpp
        include/models/Yolov7Face.h
        src/models/Yolov7Face.cpp
        include/models/YoloFaceLindevs.h
        src/models/YoloFaceLindevs.cpp
        include/models/Yolov9FaceLindevs.h
        src/models/Yolov9FaceLindevs.cpp
        include/utils/OrtInfo.h
        src/utils/OrtInfo.cpp
        include/ui/BackendSelectBox.h
        src/ui/BackendSelectBox.cpp
        include/ui/sd/Area.h
        src/ui/sd/Area.cpp
        include/ui/sd/Settings.h
        src/ui/sd/Settings.cpp
        include/models/StableDiffusionModel.h
        src/models/StableDiffusionModel.cpp
        include/models/StableDiffusionV15.h
        src/models/StableDiffusionV15.cpp
        include/sd/QStableDiffusion.h
        src/sd/QStableDiffusion.cpp
        include/models/ProgressInterface.h
        include/models/StableDiffusion35Medium.h
        src/models/StableDiffusion35Medium.cpp
        include/models/StableDiffusion35Large.h
        src/models/StableDiffusion35Large.cpp
)

add_library(${PROJECT_NAME}_core STATIC ${PROJECT_SOURCES})
add_executable(${PROJECT_NAME} main.cpp forms/mainwindow.ui resources/resource.qrc)

target_include_directories(${PROJECT_NAME}_core PUBLIC include)

target_link_libraries(${PROJECT_NAME}_core
        Qt::Widgets
        ZXing::ZXing
        Tesseract::libtesseract
        facedetection
        onnxruntime::onnxruntime
        opencv_imgcodecs
        SD::SD
)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_core)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_BINARY_DIR}/app")

if (WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)

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
    install(FILES "${CMAKE_PREFIX_PATH}/bin/onnxruntime.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    install(FILES "${CMAKE_PREFIX_PATH}/bin/stable-diffusion.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")

    if (USE_CUDA)
        cmake_path(SET CUDA_PATH $ENV{CUDA_PATH})
        install(FILES "${CMAKE_PREFIX_PATH}/lib/onnxruntime_providers_cuda.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CMAKE_PREFIX_PATH}/bin/onnxruntime_providers_shared.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CUDA_PATH}/bin/cublasLt64_12.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CUDA_PATH}/bin/cublas64_12.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CUDA_PATH}/bin/cufft64_11.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CUDA_PATH}/bin/cudart64_12.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CMAKE_PREFIX_PATH}/bin/cudnn64_9.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CMAKE_PREFIX_PATH}/bin/cudnn_graph64_9.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CMAKE_PREFIX_PATH}/bin/cudnn_ops64_9.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CMAKE_PREFIX_PATH}/bin/cudnn_engines_precompiled64_9.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CMAKE_PREFIX_PATH}/bin/cudnn_engines_runtime_compiled64_9.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
        install(FILES "${CMAKE_PREFIX_PATH}/bin/cudnn_heuristic64_9.dll" DESTINATION "${CMAKE_BINARY_DIR}/app")
    endif ()
else ()
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6Core.so.6.8.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6Core.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6Gui.so.6.8.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6Gui.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6Widgets.so.6.8.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6Widgets.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libQt6XcbQpa.so.6.8.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libQt6XcbQpa.so.6")
    install(FILES "${CMAKE_PREFIX_PATH}/plugins/platforms/libqxcb.so" DESTINATION "${CMAKE_BINARY_DIR}/app/plugins/platforms")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libopencv_core.so.4.10.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libopencv_core.so.410")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libopencv_imgproc.so.4.10.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libopencv_imgproc.so.410")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libopencv_imgcodecs.so.4.10.0" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libopencv_imgcodecs.so.410")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libtbb.so.12.14" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libtbb.so.12")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libonnxruntime.so.1.20.1" DESTINATION "${CMAKE_BINARY_DIR}/app/lib" RENAME "libonnxruntime.so.1")
    install(FILES "${CMAKE_PREFIX_PATH}/lib/libstable-diffusion.so" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")

    if (USE_CUDA)
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libonnxruntime_providers_cuda.so" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libonnxruntime_providers_shared.so" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcublasLt.so.12" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcublas.so.12" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcufft.so.11" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcudart.so.12" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcudnn.so.9" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcudnn_graph.so.9" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcudnn_ops.so.9" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcudnn_engines_precompiled.so.9" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcudnn_engines_runtime_compiled.so.9" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
        install(FILES "${CMAKE_PREFIX_PATH}/lib/libcudnn_heuristic.so.9" DESTINATION "${CMAKE_BINARY_DIR}/app/lib")
    endif ()
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif ()

message(STATUS "Build tests: " ${BUILD_TESTING})
