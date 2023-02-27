cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(polygon_decomposition)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 20)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_compile_options(-Wextra)
add_compile_options(-Wshadow)
add_compile_options(-Wconversion)
add_compile_options(-Wpedantic)
add_compile_options(-Werror)
add_compile_options(-Wno-float-equal)
add_compile_options(-g)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/test"
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/*.hh"
        "${PROJECT_SOURCE_DIR}/src/*.cc"
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

add_executable(polygon_decomp ${all_SRCS})

enable_testing()

add_executable(
  test_dcel
  src/utils.cc
  src/dcel.cc
  test/test_dcel.cc
  test/dcel_fixture.cc
)
target_link_libraries(
  test_dcel
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_dcel)