cmake_minimum_required(VERSION 3.1)
project(Headache)

# The version number.
set (Headache_VERSION_MAJOR 2)
set (Headache_VERSION_MINOR 0)

include_directories ("${PROJECT_SOURCE_DIR}/DirectX/Include")
include_directories ("${PROJECT_SOURCE_DIR}/DirectX/Lib")
include_directories ("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES WinStart.cpp)
add_executable(Headache ${SOURCE_FILES} Game.cpp Game.h Graphics/Renderer.cpp Graphics/Renderer.h Z.h Graphics/TextureManager.cpp Graphics/TextureManager.h Objects/Drawable.cpp Objects/Drawable.h Helper/Types/Size.cpp Helper/Types/Size.h Helper/Types/Position.cpp Helper/Types/Position.h)
target_link_libraries(Headache d3d9 d3dx9)

install(DIRECTORY resources/ DESTINATION resources)