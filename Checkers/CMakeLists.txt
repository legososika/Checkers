cmake_minimum_required(VERSION 3.23)
project(Checkers)

set(CMAKE_CXX_STANDARD 20)

add_executable(Checkers main.cpp Checker.h UltimatePosition.h Dummy.h Bot.h Move.h CheckArr.h)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(Checkers sfml-graphics sfml-audio)
