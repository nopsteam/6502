cmake_minimum_required(VERSION 3.17)

project(6502)

include(CTest)
include(FetchContent)
set(FETCHCONTENT_QUIET 0)

# Cmake module directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/build/cmake/")

# Uses finders in build/cmake to search for OS pre-installed package libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Download / Include Unity Test Runner
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG        master)

# Download / Include Commons libs SC String
FetchContent_Declare(
  sc_lib
  GIT_REPOSITORY https://github.com/tezc/sc.git
  GIT_TAG        master)
SET(SC_BUILD_TEST OFF CACHE BOOL "Turn off sc_lib tests" FORCE)

FetchContent_MakeAvailable(unity sc_lib)

# Output directory structure configuration.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(TEST_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/test")

# Add symbolic link to resources folder in build
add_custom_target(resources)
FILE(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/resources" source)
FILE(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/resources" destination)
IF (WIN32)
  add_custom_command(
    TARGET resources POST_BUILD
    COMMAND mklink /D ${destination} ${source}
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
    )
ELSE()
  add_custom_command(
    TARGET resources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
    )
ENDIF()

# Generates a compile_commands.json file containing the exact compiler calls
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
FILE(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/compile_commands.json" sourceJson)
FILE(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/build/compile_commands.json" destinationJson)
add_custom_command(TARGET resources POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy 
  ${sourceJson} ${destinationJson}
  COMMENT "Copying compile_commands.json to build directory")

# Project-wide include directory configuration.
include_directories("${PROJECT_SOURCE_DIR}/src")

# Project library source lives in src/.
add_subdirectory(src)

# Project apps that may link to project libraries live in app/.
add_subdirectory(app)

# CTest sets BUILD_TESTING option to ON by default.
# Test-related configuration goes here.
if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)

  # COVERAGE
  if (${CMAKE_BUILD_TYPE} MATCHES "Coverage")
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
      add_compile_options(--coverage)
      link_libraries(gcov)
    else ()
      message(FATAL_ERROR "Only GCC is supported for coverage")
    endif ()
  endif ()

  add_custom_target(coverage)
  add_custom_command(
    TARGET coverage
    COMMAND make test

    COMMAND lcov --capture --directory "${PROJECT_BINARY_DIR}/src/CMakeFiles"
    --output-file "${PROJECT_BINARY_DIR}/coverage.info" --rc lcov_branch_coverage=1 --rc lcov_excl_br_line='assert'
    COMMAND lcov --remove "${PROJECT_BINARY_DIR}/coverage.info" '/usr/*' '*test*'
    --output-file "${PROJECT_BINARY_DIR}/coverage.info" --rc lcov_branch_coverage=1 --rc lcov_excl_br_line='assert'
    COMMAND lcov --list "${PROJECT_BINARY_DIR}/coverage.info" --rc lcov_branch_coverage=1 --rc lcov_excl_br_line='assert'
    )
endif()
