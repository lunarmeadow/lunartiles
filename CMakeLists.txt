# partially adapted from barrett's cmake, thank you erysdren :3

cmake_minimum_required(VERSION 3.11)
project(lunartiles
DESCRIPTION "A level editor for the Moonbeam engine."
HOMEPAGE_URL "https://github.com/lunarmeadow/lunartiles"
LANGUAGES C CXX
)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_C_STANDARD 23)

option(USE_ASAN "Turn on ASAN" OFF)

# DEPENDENCIES

include(FetchContent)

# https://github.com/raysan5/raylib/blob/master/projects/CMake/CMakeLists.txt
set(RAYLIB_VERSION 6.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

FetchContent_Declare(
    miniz
    GIT_REPOSITORY https://github.com/richgel999/miniz.git
    GIT_TAG 3.1.0
    EXCLUDE_FROM_ALL
)

FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 4.0
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(miniz raygui)

# LIBRARY CONFIG

add_library(ASAN::ASAN IMPORTED INTERFACE)
target_compile_options(ASAN::ASAN INTERFACE -fsanitize=address,undefined $<$<NOT:$<COMPILE_LANG_AND_ID:C,MSVC>>:-fno-omit-frame-pointer>)
target_link_options(ASAN::ASAN INTERFACE -fsanitize=address,undefined)

# ADD ALL SOURCE FILES

set(SOURCES
${PROJECT_SOURCE_DIR}/src/main.c
${PROJECT_SOURCE_DIR}/src/ui/tilegrid.c
${PROJECT_SOURCE_DIR}/src/ui/viewport.c
)

# BUILD TARGET CONFIG

add_executable(lunartiles ${SOURCES})
target_link_libraries(lunartiles PRIVATE raylib miniz)
target_link_libraries(lunartiles PUBLIC $<$<BOOL:${USE_ASAN}>:ASAN::ASAN>)
target_include_directories(lunartiles PRIVATE ${raylib_SOURCE_DIR}/src)
target_include_directories(lunartiles PRIVATE ${raygui_SOURCE_DIR}/src)
target_include_directories(lunartiles PRIVATE ${raygui_SOURCE_DIR}/styles/lavanda)

# BUILD TYPES / COMPILE OPTIONS

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "CLANG")
    target_compile_options(lunartiles PRIVATE -Wall -Wextra -Wshadow=compatible-local -Wpedantic -Wfatal-errors)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(lunartiles PRIVATE -g -O0)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(lunartiles PRIVATE -O2)
endif()

if(WIN32)
    if(MINGW)
        target_link_options(lunartiles PRIVATE -static-libgcc -static-libstdc++ -static)
    endif()
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT WIN32)
    target_link_options(lunartiles PRIVATE -rdynamic)
endif()
