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

target_link_libraries(
  sdl
  ${SDL2_LIBRARIES}
  m
)

target_link_libraries(
  cpu
  bus
)

target_link_libraries(
  disassembler
  constants
  sc_str
  sc_array
)
