
cmake_minimum_required(VERSION 3.10)

project(MinHeap VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++-9)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -stdlib=libc++ -glldb")
add_executable(main main.cpp)
add_executable(test test.cpp)
target_include_directories(main PUBLIC include)
target_include_directories(test PUBLIC include)
