cmake_minimum_required(VERSION 3.8)
project(SmallProjects)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/status.h src/status.cpp include/export.h include/slice.h src/slice.cpp include/filename.h src/filename.cpp include/arena.h src/arena.cpp test/arena_test.cpp include/random.h)
add_executable(SmallProjects ${SOURCE_FILES})