cmake_minimum_required(VERSION 3.12)

project(gameoflife VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/world.cpp
    src/gameoflife.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)