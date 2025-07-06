cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(rpg-raylib C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES src/main.c src/utils.c src/game.c src/pause.c src/battle.c
            src/map.c)

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

# required for TMX library
find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)

find_package(tmx 1.10 QUIET)
if(NOT tmx_FOUND)
  include(FetchContent)
  set(FETCHCONTENT_QUIET FALSE)

  FetchContent_Declare(
    tmx
    GIT_REPOSITORY https://github.com/baylej/tmx
    GIT_TAG tmx_1.10.0
    GIT_PROGRESS TRUE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(DEBUG)
endif()

# Target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib tmx LibXml2::LibXml2
                                              ZLIB::ZLIB)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(WIN32)
  set(PLATFORM_LIBS winmm opengl32 gdi32 glu32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})
elseif(APPLE)
  target_link_libraries(
    ${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa"
                            "-framework OpenGL")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Code quality targets
if(WIN32)
  set(CLANG_TIDY_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/clang-tidy.bat")
  set(CLANG_FORMAT_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/clang-format.bat")
else()
  set(CLANG_TIDY_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/clang-tidy.sh")
  set(CLANG_FORMAT_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/clang-format.sh")
endif()

# Add clang-tidy target
add_custom_target(tidy
  COMMAND ${CLANG_TIDY_SCRIPT} ${SOURCES}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Running clang-tidy"
  VERBATIM
)

# Add clang-format target
add_custom_target(format
  COMMAND ${CLANG_FORMAT_SCRIPT} -i ${SOURCES}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Running clang-format"
  VERBATIM
)
