cmake_minimum_required(VERSION 3.28)
project(SDL3Engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(FetchContent)

# ---- SDL3 ----
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

# ---- OpenGL ----
find_package(OpenGL REQUIRED)

# ---- GLAD (vendored) ----
add_library(glad STATIC
  external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

# ---- Your executable ----
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_executable(SDL3Engine ${ENGINE_SOURCES})

target_include_directories(SDL3Engine PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SDL3Engine PRIVATE
  SDL3::SDL3
  glad
  OpenGL::GL
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(SDL3Engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
