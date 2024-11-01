cmake_minimum_required(VERSION 3.28)
project(assistant_tests)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
        utils/DateTime_test.cpp
        utils/Formatting_test.cpp
        utils/ImgProc_test.cpp
        models/Yolov5Face_test.cpp
        models/Yolov7Face_test.cpp
        models/Yolov8FaceLindevs_test.cpp
        models/UltraFace_test.cpp
        models/YoloFaceV2_test.cpp
        models/RetinaFace_test.cpp
        models/Libfacedetection_test.cpp
        models/MobileNetV3Dedup_test.cpp
        models/ModNet_test.cpp
        face/IdPhotoCreator_test.cpp
)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} GTest::gtest_main gmock ${CMAKE_PROJECT_NAME}_core)

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Images
FetchContent_Declare(
        testsdata
        GIT_REPOSITORY https://github.com/lindevs/assistant-testsdata.git
        GIT_TAG master
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/testsdata/images
        GIT_SHALLOW 1
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)
FetchContent_MakeAvailable(testsdata)

# Models
file(DOWNLOAD https://github.com/clibdev/yolov5-face/releases/latest/download/yolov5n-0.5-face.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/yolov5n-0.5-face.onnx
        EXPECTED_HASH SHA256=269eb1e54313f9d1f7941ed9939fa247767539bca5801fc7aa7895960e93ca43 SHOW_PROGRESS
)
file(DOWNLOAD https://github.com/clibdev/yolov7-face/releases/latest/download/yolov7-lite-t-face.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/yolov7-lite-t-face.onnx
        EXPECTED_HASH SHA256=448b3ad27119ca15f629d9e83fe4e8c71a783c0358a154f5f4f9197320a0c89d SHOW_PROGRESS
)
file(DOWNLOAD https://github.com/lindevs/yolov8-face/releases/latest/download/yolov8n-face-lindevs.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/yolov8n-face-lindevs.onnx
        EXPECTED_HASH SHA256=8d0bfb0c3383c5bd7a78dd24ef79a21e2aa456619b6ab5e53867092d1c7dc414 SHOW_PROGRESS
)
file(DOWNLOAD https://github.com/clibdev/Ultra-Light-Fast-Generic-Face-Detector-1MB/releases/latest/download/ultraface-rfb-640.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/ultraface-rfb-640.onnx
        EXPECTED_HASH SHA256=a3d2fa1ccd444f244716d96fcf0d32d454e422cb8163faa840f80968e25d6f77 SHOW_PROGRESS
)
file(DOWNLOAD https://github.com/clibdev/YOLO-FaceV2/releases/latest/download/yolo-facev2.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/yolo-facev2.onnx
        EXPECTED_HASH SHA256=8ad769e4e9fd5869baa4243367e041df901a228e121a1602deec85074d2bd7ed SHOW_PROGRESS
)
file(DOWNLOAD https://github.com/clibdev/Pytorch_Retinaface/releases/latest/download/retinaface-mobilenet-0.25.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/retinaface-mobilenet-0.25.onnx
        EXPECTED_HASH SHA256=4aa128919a621c913b3bf78befa33eaaba086a7a7e142cdb739839a9340f2420 SHOW_PROGRESS
)
file(DOWNLOAD https://github.com/clibdev/imagededup/releases/latest/download/mobilenetv3-small-dedup.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/mobilenetv3-small-dedup.onnx
        EXPECTED_HASH SHA256=cfdb10bd95a6b02c1c41618e2d9037d0ca835279c6d8b4d93553a7a04c5ca327 SHOW_PROGRESS
)
file(DOWNLOAD https://github.com/clibdev/MODNet/releases/latest/download/modnet-photographic.onnx
        ${CMAKE_SOURCE_DIR}/testsdata/models/modnet-photographic.onnx
        EXPECTED_HASH SHA256=d381d71c0e85f0edc28df99a6dd59544b0c33cc2bf234b1fc22aa417fec127be SHOW_PROGRESS
)

file(COPY ${CMAKE_SOURCE_DIR}/testsdata DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
