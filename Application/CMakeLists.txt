cmake_minimum_required(VERSION 3.10)

project(Client)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)
include_directories(Client)
include_directories(files)

add_subdirectory(src)

add_executable(Client src/main.cpp)

target_link_libraries(Client sfml-graphics sfml-window sfml-system src)