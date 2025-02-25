cmake_minimum_required(VERSION 3.12)

project(raylib-game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
  src/main.c
  src/utils.c
)

set(HEADERS
  src/utils.h
  src/player.h
)

find_package(raylib 5.5 QUIET)

if(NOT raylib_FOUND)
  include(FetchContent)
  set(FETCHCONTENT_QUIET FALSE)

  set(BUILD_EXAMPLES
      OFF
      CACHE BOOL "" FORCE)
  set(BUILD_SHARED_LIBS
      OFF
      CACHE BOOL "" FORCE)
  set(USE_MSVC_RUNTIME_LIBRARY_DLL
      ON
      CACHE BOOL "" FORCE)

  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_PROGRESS TRUE)

  FetchContent_MakeAvailable(raylib)
  set(RAYLIB_LIBRARY raylib)
else()
  set(RAYLIB_LIBRARY raylib)
endif()

if(WIN32)
  set(PLATFORM_LIBS winmm opengl32 gdi32 glu32)
endif()

# Target
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY})

if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})
elseif(APPLE)
  target_link_libraries(
    ${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa"
                            "-framework OpenGL")
endif()
