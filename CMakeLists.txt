cmake_minimum_required(VERSION 3.12)
project(raylib-game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

if (WIN32)
  # Windows
  include(FetchContent)
  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5.0
  )
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(raylib)
  set(RAYLIB_LIBRARY raylib)
else()
  # Unix
  find_package(raylib 5.5 REQUIRED)
  set(RAYLIB_LIBRARY raylib)
endif()

# Target
add_executable(${PROJECT_NAME}
  src/main.c
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY})

if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
endif()
