cmake_minimum_required(VERSION 3.28)
project(assistant_tests)

include(${CMAKE_SOURCE_DIR}/cmake/helpers.cmake)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.16.0
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
        utils/DateTime_test.cpp
        utils/Formatting_test.cpp
        utils/ImgProc_test.cpp
        models/Yolov5Face_test.cpp
        models/Yolov7Face_test.cpp
        models/Yolov8FaceLindevs_test.cpp
        models/Yolov9FaceLindevs_test.cpp
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

target_compile_definitions(${PROJECT_NAME} PRIVATE -DTESTS_DATA="${CMAKE_SOURCE_DIR}/testsdata")

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set(IMAGES
        "detection/face.jpg|536b29cd513fb618e4d5aa79d51a279948daa804ce359463449cce5f9dc68aa7"
        "generic/dog.jpg|3d0e1dc3ace4a67a9e7a48996cfddbb7543de9e38b3a640e16ad7e599d44b816"
        "id_photo/alpha.bmp|a07be6e335bbb5539049f7cde3e07aea813c73fc6a511e56fa1ff17101111d65"
        "id_photo/face.jpg|35c25618f913506f0c03943f9260622251ba417b20af92c4257aa5a15503aa8c"
        "id_photo/result.png|286fb43067354bec1a16ec2e05471aaa2edc7c14c4e3d035f0ea34023aa422de"
        "result/modnet.bmp|f4b77413152520dd2d2edc8886aad28244d48646df4ff55d34d58b0fb6446180"
)
github_file_download(IMAGES ${CMAKE_SOURCE_DIR}/testsdata/images lindevs/assistant-testsdata)

set(MODELS
        "https://github.com/clibdev/yolov5-face/releases/latest/download/yolov5n-0.5-face.onnx|269eb1e54313f9d1f7941ed9939fa247767539bca5801fc7aa7895960e93ca43"
        "https://github.com/clibdev/yolov7-face/releases/latest/download/yolov7-lite-t-face.onnx|448b3ad27119ca15f629d9e83fe4e8c71a783c0358a154f5f4f9197320a0c89d"
        "https://github.com/lindevs/yolov8-face/releases/latest/download/yolov8n-face-lindevs.onnx|8d0bfb0c3383c5bd7a78dd24ef79a21e2aa456619b6ab5e53867092d1c7dc414"
        "https://github.com/lindevs/yolov9-face/releases/latest/download/yolov9t-face-lindevs.onnx|7766f85cecd7045a1b64cf3a89d94819c62cc5ff24b782b86bb0dec4f9e31964"
        "https://github.com/clibdev/Ultra-Light-Fast-Generic-Face-Detector-1MB/releases/latest/download/ultraface-rfb-640.onnx|a3d2fa1ccd444f244716d96fcf0d32d454e422cb8163faa840f80968e25d6f77"
        "https://github.com/clibdev/YOLO-FaceV2/releases/latest/download/yolo-facev2.onnx|8ad769e4e9fd5869baa4243367e041df901a228e121a1602deec85074d2bd7ed"
        "https://github.com/clibdev/Pytorch_Retinaface/releases/latest/download/retinaface-mobilenet-0.25.onnx|4aa128919a621c913b3bf78befa33eaaba086a7a7e142cdb739839a9340f2420"
        "https://github.com/clibdev/imagededup/releases/latest/download/mobilenetv3-small-dedup.onnx|cfdb10bd95a6b02c1c41618e2d9037d0ca835279c6d8b4d93553a7a04c5ca327"
        "https://github.com/clibdev/MODNet/releases/latest/download/modnet-photographic.onnx|d381d71c0e85f0edc28df99a6dd59544b0c33cc2bf234b1fc22aa417fec127be"
)
file_download(MODELS ${CMAKE_SOURCE_DIR}/testsdata/models)
