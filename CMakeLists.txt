cmake_minimum_required(VERSION 3.20)

project(MiniCAD VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(minicad_lib
    src/minicad.cpp
)

target_include_directories(minicad_lib PUBLIC include)

add_executable(minicad src/main.cpp)
target_link_libraries(minicad PRIVATE minicad_lib)

if(MSVC)
    target_compile_options(minicad_lib PRIVATE /W4 /permissive-)
else()
    target_compile_options(minicad_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(minicad_tests tests/minicad_test.cpp)
    target_link_libraries(minicad_tests PRIVATE minicad_lib)
    add_test(NAME minicad_tests COMMAND minicad_tests)
endif()
