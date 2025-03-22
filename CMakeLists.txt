cmake_minimum_required(VERSION 3.10)

project(patients)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Server)
add_subdirectory(Client)
