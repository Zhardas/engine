cmake_minimum_required(VERSION 3.1)
project(Headache)

# The version number.
set (Headache_VERSION_MAJOR 2)
set (Headache_VERSION_MINOR 0)

include_directories ("${PROJECT_SOURCE_DIR}/lib/directx9/Include")
include_directories ("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
    Helper/Types/Size.cpp
    Helper/Types/Size.h
    Helper/Types/Position.cpp
    Helper/Types/Position.h
    Objects/TexturedQuad.cpp
    Objects/TexturedQuad.h
    Scene/Scene.cpp
    Scene/Scene.h Input/Input.cpp Input/Input.h Helper/input.h)

target_link_libraries(Headache d3d9 d3dx9 dinput8 dxguid)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${DESTINATION}/)