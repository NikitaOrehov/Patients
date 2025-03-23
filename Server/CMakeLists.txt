cmake_minimum_required(VERSION 3.10)

project(Server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PostgreSQL REQUIRED)

include_directories(include)

add_subdirectory(src)

add_executable(Server src/main.cpp src/DataBaseWorker.cpp)

target_link_libraries(Server PostgreSQL::PostgreSQL server_src)