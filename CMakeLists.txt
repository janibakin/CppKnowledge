cmake_minimum_required(VERSION 3.16)
project(CppKnowledge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB source_files "*.cpp")

foreach(file ${source_files})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file}
            customAllocArena.cpp)
endforeach()
