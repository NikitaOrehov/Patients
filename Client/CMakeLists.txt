cmake_minimum_required(VERSION 3.10)

project(Client)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Client main.cpp)

target_link_libraries(Client sfml-graphics sfml-window sfml-system)