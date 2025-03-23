cmake_minimum_required(VERSION 3.10)

project(Server)

add_library(server_src SHARED ConnectionHandler.cpp)