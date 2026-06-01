cmake_minimum_required(VERSION 3.20)
project(learn_cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(learn_cmake
    main.cpp
)

target_compile_options(learn_cmake PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wconversion
)