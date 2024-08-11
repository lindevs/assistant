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
)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} GTest::gtest_main ${CMAKE_PROJECT_NAME}_core)

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
