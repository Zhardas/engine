cmake_minimum_required(VERSION 3.1)
project(Headache)

# The version number.
set (Headache_VERSION_MAJOR 2)
set (Headache_VERSION_MINOR 0)

include_directories (SYSTEM "${PROJECT_SOURCE_DIR}/lib/dx/include/")
include_directories (SYSTEM "${PROJECT_SOURCE_DIR}/lib/vorbis/include/")
include_directories (SYSTEM "${PROJECT_SOURCE_DIR}/lib/vorbis/lib/")
include_directories ("${PROJECT_SOURCE_DIR}")
#include_directories ("F:/mingw-w64/i686-4.9.2-posix-dwarf-rt_v4-rev2/mingw32/i686-w64-mingw32/include")
#include_directories ("F:/mingw-w64/i686-4.9.2-posix-dwarf-rt_v4-rev2/mingw32/i686-w64-mingw32/include/c++/i686-w64-mingw32")
#include_directories ("F:/mingw-w64/i686-4.9.2-posix-dwarf-rt_v4-rev2/mingw32/i686-w64-mingw32/include/c++")
link_directories(${PROJECT_SOURCE_DIR}/lib/dx/lib/x86/)
link_directories(${PROJECT_SOURCE_DIR}/lib/vorbis/lib/)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_executable(Headache
    WinStart.cpp
    Z.h
    Game.cpp
    Game.h
    Graphics/Renderer.cpp
    Graphics/Renderer.h
    Graphics/TextureManager.cpp
    Graphics/TextureManager.h
    Objects/Drawable.cpp
    Objects/Drawable.h
    Objects/TexturedQuad.cpp
    Objects/TexturedQuad.h
    Scene/Scene.cpp
    Scene/Scene.h
    Helper/input.h
    Audio/AudioManager.h
    Audio/AudioManager.cpp
    Helper/types.h Audio/Audio.cpp Audio/Audio.h)

target_link_libraries(Headache d3d9 d3dx9 dinput8 dxguid vorbis ogg vorbisfile)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${DESTINATION}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/vorbis/lib/libvorbis.dll DESTINATION ${DESTINATION}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/vorbis/lib/libvorbisfile.dll DESTINATION ${DESTINATION}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/vorbis/lib/libogg.dll DESTINATION ${DESTINATION}/)