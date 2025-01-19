cmake_minimum_required(VERSION 3.12)

if (WIN32)
  if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
  endif()
endif()

project(raylib-game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

if (WIN32)
  # Windows
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
  set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "" FORCE)

  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_PROGRESS TRUE
  )

  FetchContent_MakeAvailable(raylib)
  set(RAYLIB_LIBRARY raylib)
  set(PLATFORM_LIBS winm opengl32 gdi32)
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

if (WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
endif()
