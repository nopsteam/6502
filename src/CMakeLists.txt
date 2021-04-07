add_library(
  constants SHARED
  constants.c
)

add_library(
  disassembler SHARED
  disassembler.c
)

add_library(
  bus SHARED
  bus.c
)

add_library(
  cpu SHARED
  cpu.c
)

add_library(
  sdl SHARED
  sdl.c
)
  
add_library(
  opcodes SHARED
  opcodes.c
)


target_link_libraries(
  sdl
  ${SDL2_LIBRARIES}
  m
)

target_link_libraries(
  cpu
  bus
  opcodes
  disassembler
)

target_link_libraries(
  disassembler
  constants
  sc_str
  sc_array
)


###################################################################

# COVERAGE
if (${CMAKE_BUILD_TYPE} MATCHES "Coverage")
  if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    file(GLOB ALL_SRC_C_FILES "*.c")

    foreach(src ${ALL_SRC_C_FILES}) 
      get_filename_component(name ${src} NAME_WLE)
      message(STATUS "Coverage build for: ${name}")
      target_compile_options(${name} PRIVATE --coverage)
      target_link_libraries(${name} gcov)
    endforeach(src)

  else ()
    message(FATAL_ERROR "Only GCC is supported for coverage")
  endif ()
endif ()
