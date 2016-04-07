cmake_minimum_required(VERSION 3.1)
project(headache2)

# The version number.
set(Headache_VERSION_MAJOR 1)
set(Headache_VERSION_MINOR 0)

include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/lib/dx/include/")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/lib/vorbis/include/")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/lib/enet/include")
include_directories("${PROJECT_SOURCE_DIR}")
link_directories(${PROJECT_SOURCE_DIR}/lib/dx/lib/x86/)
link_directories(${PROJECT_SOURCE_DIR}/lib/vorbis/lib/)
link_directories(${PROJECT_SOURCE_DIR}/lib/enet/lib/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -std=c++14 -Wall -Wno-unused-function")

add_library(headache2
        game.cpp
        game.h
        graphics/renderer.cpp
        graphics/renderer.h
        graphics/texture_manager.cpp
        graphics/texture_manager.h
        graphics/font.cpp
        graphics/font.h
        graphics/layers/layer.cpp
        graphics/layers/layer.h
        scene/scene.cpp
        scene/scene.h
        audio/audio_manager.h
        audio/audio_manager.cpp
        audio/audio.cpp
        audio/audio.h
        helper/input.h
        helper/types.h
        input/input_manager.cpp
        input/input_manager.h
        objects/drawable.h
        objects/drawable.cpp
        objects/textured_quad.h
        objects/textured_quad.cpp
        objects/text.h
        objects/text.cpp
        objects/camera.h
        objects/camera.cpp
        objects/common/console.cpp
        objects/common/console.h
        helper/helper.h
        networking/network_manager.cpp
        networking/network_manager.h
        networking/client.cpp
        networking/client.h
        objects/common/button.cpp
        objects/common/button.h
        objects/common/textbox.cpp
        objects/common/textbox.h
        objects/common/checkbox.cpp
        objects/common/checkbox.h
        objects/common/listbox.cpp
        objects/common/listbox.h)

target_link_libraries(headache2 d3d9 d3dx9 dinput8 dxguid vorbis ogg vorbisfile enet Ws2_32 Winmm)