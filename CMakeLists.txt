cmake_minimum_required(VERSION 3.1)
project(headache)

# The version number.
set (Headache_VERSION_MAJOR 2)
set (Headache_VERSION_MINOR 0)

include_directories (SYSTEM "${PROJECT_SOURCE_DIR}/lib/dx/include/")
include_directories (SYSTEM "${PROJECT_SOURCE_DIR}/lib/vorbis/include/")
include_directories ("${PROJECT_SOURCE_DIR}")
#include_directories ("F:/mingw-w64/i686-4.9.2-posix-dwarf-rt_v4-rev2/mingw32/i686-w64-mingw32/include")
#include_directories ("F:/mingw-w64/i686-4.9.2-posix-dwarf-rt_v4-rev2/mingw32/i686-w64-mingw32/include/c++/i686-w64-mingw32")
#include_directories ("F:/mingw-w64/i686-4.9.2-posix-dwarf-rt_v4-rev2/mingw32/i686-w64-mingw32/include/c++")
link_directories(${PROJECT_SOURCE_DIR}/lib/dx/lib/x86/)
link_directories(${PROJECT_SOURCE_DIR}/lib/vorbis/lib/)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(headache
        game.cpp
        game.h
        graphics/renderer.cpp
        graphics/renderer.h
        graphics/texture_manager.cpp
        graphics/texture_manager.h
        objects/drawable.cpp
        objects/drawable.h
        objects/textured_quad.cpp
        objects/textured_quad.h
        scene/scene.cpp
        scene/scene.h
        helper/input.h
        audio/audio_manager.h
        audio/audio_manager.cpp
        helper/types.h
        audio/audio.cpp
        audio/audio.h
        input/input_manager.cpp
        input/input_manager.h
        graphics/font.cpp
        graphics/font.h
        objects/text.cpp
        objects/text.h
        graphics/layers/layer.cpp
        graphics/layers/layer.h
        graphics/layers/layer_drawable.cpp
        graphics/layers/layer_drawable.h
        graphics/layers/layer_text.cpp
        graphics/layers/layer_text.h
        objects/camera.cpp
        objects/camera.h)

target_link_libraries(headache d3d9 d3dx9 dinput8 dxguid vorbis ogg vorbisfile)