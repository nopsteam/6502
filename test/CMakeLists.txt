# Include Unity test framework.
add_subdirectory(unity)

# Configure an disassembler test binary.
add_executable(
  disassembler_test
  disassembler_test.c
)
target_link_libraries(
  disassembler_test
  unity
  disassembler
)

target_include_directories(
  disassembler_test PUBLIC
  ${PROJECT_SOURCE_DIR}/test/unity
)

set_target_properties(
  disassembler_test
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}"
)

add_test(disassembler_test "${TEST_OUTPUT_PATH}/disassembler_test")
