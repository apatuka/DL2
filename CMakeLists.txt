cmake_minimum_required(VERSION 3.21)
project(Deadlock2 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2 (vcpkg: `vcpkg install sdl2`). Configure with
#   -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
find_package(SDL2 CONFIG REQUIRED)

option(DL2_BUILD_TOOLS "Build command-line asset tools" ON)
include(CTest)
set(DL2_DATA_DIR "$ENV{DL2_DATA}" CACHE PATH "Original game installation for optional asset tests (read-only)")

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
