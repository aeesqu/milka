cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(milka LANGUAGES CXX)

add_executable(milka
  src/main.cpp
  # Core
  src/core/context.cpp
  src/core/window.cpp
  src/core/logging.cpp
  # Events
  src/events/event.cpp
  # Graphics
  src/graphics/renderer.cpp
  src/graphics/rendererInternal.cpp
  src/graphics/vertexBuffer.cpp
  # d3d9
  src/graphics/d3d9/d3d9_renderer.cpp
  src/graphics/d3d9/d3d9_vertex.cpp
  src/graphics/d3d9/d3d9_vertexBuffer.cpp
  )

target_include_directories(milka PUBLIC
  include/
  thirdparty/)

target_link_libraries(milka PUBLIC
  ${CMAKE_SOURCE_DIR}/dependencies/win32/SDL2main.lib
  ${CMAKE_SOURCE_DIR}/dependencies/win32/SDL2.lib
  d3d9
  d3dx9
  d3dcompiler
  )
