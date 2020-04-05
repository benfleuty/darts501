cmake_minimum_required(VERSION 3.15)
project(Darts501)

set(CMAKE_CXX_STANDARD 14)

add_executable(Darts501 main.cpp Player.cpp Player.h UserIO.cpp UserIO.h Game.cpp Game.h Target.cpp Target.h)
