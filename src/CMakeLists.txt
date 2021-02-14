add_library(
  constants SHARED
  constants.c
)

add_library(
  disassembler SHARED
  disassembler.c
)

target_link_libraries(
  disassembler
  constants
  sc_str
  sc_array
)
