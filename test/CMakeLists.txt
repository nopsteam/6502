# Config
set(SC_BUILD_TEST OFF)

# Opcodes test folder
add_subdirectory(opcodes)

# 1. Declare the test file
set(Tests
  bus_test
  cpu_test
  opcodes_test
  disassembler_test
  program_test)

# 2. Declare dependencies of each test file
set(bus_test_deps
  bus)

set(cpu_test_deps
  cpu)

set(opcodes_test_deps
  opcodes
  cpu)

set(disassembler_test_deps
  disassembler)

set(program_test_deps
  disassembler)

# 3. Add dependencies to a list, need to be in the same order as item 1
set(Dependencies
  bus_test_deps
  cpu_test_deps
  opcodes_test_deps
  disassembler_test_deps
  program_test_deps)

###################################################################

foreach(tst deps IN ZIP_LISTS Tests Dependencies)
  message(STATUS "test=${tst}, dependencies=${deps}")
  add_executable(
    ${tst}
    ${tst}.c)

  target_link_libraries(
    ${tst}
    unity)

  foreach(dep ${${deps}})
    message(STATUS "-> test=${tst}, dependency=${dep}")
    target_link_libraries(
      ${tst}
      ${dep})
  endforeach(dep)

  target_include_directories(
    ${tst} PUBLIC
    ${PROJECT_SOURCE_DIR}/test/unity)

  set_target_properties(
    ${tst}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}")

  add_test(${tst} "${TEST_OUTPUT_PATH}/${tst}")
endforeach()

set_tests_properties(
  disassembler_test PROPERTIES
  ENVIRONMENT DATADIR=${PROJECT_BINARY_DIR}/resources/dump.bin)

set_tests_properties(
  bus_test PROPERTIES
  ENVIRONMENT DATADIR=${PROJECT_BINARY_DIR}/resources/dump.bin)
