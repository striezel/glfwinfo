cmake_minimum_required (VERSION 3.8)

project(glfwinfo)

set(glfwinfo_sources
    glfw.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions (-Wall -Wextra -Wpedantic -pedantic-errors -Wshadow -fexceptions)

    if (CODE_COVERAGE)
        add_definitions (-O0)
    else()
        add_definitions (-O2)
    endif()

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(glfwinfo ${glfwinfo_sources})

# GNU GCC before 9.1.0 needs to link to libstdc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0")
  target_link_libraries(glfwinfo stdc++fs)
endif ()

# Clang before 9.0 needs to link to libc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0")
    # If we are on Clang 7.x, then the filesystem library from GCC is better.
    target_link_libraries(glfwinfo stdc++fs)
  else ()
    # Use Clang's C++ filesystem library, it is recent enough.
    target_link_libraries(glfwinfo c++fs)
  endif ()
endif ()

# libGL
find_package (OpenGL REQUIRED COMPONENTS OpenGL)
if (OpenGL_OpenGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  target_link_libraries (glfwinfo ${OPENGL_LIBRARIES})
else ()
  message ( FATAL_ERROR "libGL was not found!" )
endif ()

# GLFW for window handling
find_package (glfw3 REQUIRED)
if (glfw3_FOUND)
  target_link_libraries (glfwinfo glfw)
else ()
  message ( FATAL_ERROR "GLFW was not found!" )
endif ()

# #################### #
# tests for executable #
# #################### #

# add tests for --version and --help parameters
# default help parameter "--help"
add_test(NAME glfwinfo_help
         COMMAND $<TARGET_FILE:glfwinfo> --help)

# short help parameter with question mark "-?"
add_test(NAME glfwinfo_help_question_mark
         COMMAND $<TARGET_FILE:glfwinfo> -?)

# Windows-style help parameter "/?"
if (NOT DEFINED ENV{GITHUB_ACTIONS} OR NOT MINGW)
  add_test(NAME glfwinfo_help_question_mark_windows
           COMMAND $<TARGET_FILE:glfwinfo> /?)
endif ()

# parameter to show version number
add_test(NAME glfwinfo_version
         COMMAND $<TARGET_FILE:glfwinfo> --version)
