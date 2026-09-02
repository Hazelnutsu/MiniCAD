cmake_minimum_required(VERSION 3.20)

project(MiniCAD VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(minicad_lib
    src/minicad.cpp
    src/point.cpp
    src/segment.cpp
    src/vector2D.cpp
    src/numeric.cpp
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
    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.15.3
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(Catch2)

    add_executable(minicad_tests
        tests/minicad_test.cpp
    )

    target_link_libraries(minicad_tests
        PRIVATE
            minicad_lib
            Catch2::Catch2WithMain
    )

    list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
    include(Catch)
    catch_discover_tests(minicad_tests)
endif()
