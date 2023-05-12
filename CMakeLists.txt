cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(polygon_decomposition)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 20)
option(BUILD_DOC "Build documentation" ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_compile_options(-Wextra)
add_compile_options(-D_GLIBCXX_DEBUG)
add_compile_options(-Wshadow)
add_compile_options(-Wconversion)
add_compile_options(-Wpedantic)
add_compile_options(-Werror)
# add_compile_options(-fsanitize=address)
# add_compile_options(-fsanitize=undefined)
add_compile_options(-Wno-float-equal)
add_compile_options(-Wno-variadic-macros)
add_compile_options(-g)
# add_link_options(-fsanitize=address)
# add_link_options(-fsanitize=undefined)


include_directories(
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/test"
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/*.hh"
        "${PROJECT_SOURCE_DIR}/src/*.cc"
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

file(GLOB visualize_src
  "${PROJECT_SOURCE_DIR}/utils/visualize.cc"
)

file(GLOB benchmark_src
  "${PROJECT_SOURCE_DIR}/src/dcel.cc"
  "${PROJECT_SOURCE_DIR}/src/decomp.cc"
  "${PROJECT_SOURCE_DIR}/src/merge.cc"
  "${PROJECT_SOURCE_DIR}/src/utils.cc"
  "${PROJECT_SOURCE_DIR}/utils/benchmark.cc"
)

add_executable(polygon_decomp ${all_SRCS})
add_executable(visualize ${visualize_src})
add_executable(benchmark ${benchmark_src})

add_custom_command(TARGET polygon_decomp POST_BUILD COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json)

find_package(Doxygen
             REQUIRED dot
             OPTIONAL_COMPONENTS mscgen dia)

set(DOXYGEN_GENERATE_HTML YES)
doxygen_add_docs(
    doxygen
    "${PROJECT_SOURCE_DIR}/src"
    COMMENT "Generate html pages"
)
