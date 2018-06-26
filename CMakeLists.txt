cmake_minimum_required(VERSION 3.9)
project(flaskServerCreator)

set(CMAKE_CXX_STANDARD 11)

add_executable(flaskServerCreator main.cpp Website.cpp Website.h ServerCreator.cpp ServerCreator.h)