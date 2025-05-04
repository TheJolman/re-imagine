cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(raylib-game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES src/main.c src/utils.c src/game.c src/pause.c src/battle.c)

# Check for raylib and install it if it's not found
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
  if(WIN32)
    set(USE_MSVC_RUNTIME_LIBRARY_DLL
        ON
        CACHE BOOL "" FORCE)
  endif()

  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_PROGRESS TRUE)

  FetchContent_MakeAvailable(raylib)
endif()

# Check for raylib tileson and install if it's not found
find_package(raylib-tileson REQUIRED)

# Target
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE stdc++)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib-tileson)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(WIN32)
  set(PLATFORM_LIBS winmm opengl32 gdi32 glu32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})
elseif(APPLE)
  target_link_libraries(
    ${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa"
                            "-framework OpenGL")
endif()
