# Main emulator
add_executable(
  6502
  6502.c
)

target_link_libraries(
  6502
  sdl
  bus
)

# Disassembler
add_executable(
  6502_disasm
  6502_disasm.c
)

target_link_libraries(
  6502_disasm
  disassembler
)

add_dependencies(6502_disasm resources)
