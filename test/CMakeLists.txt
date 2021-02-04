# Config

# 1. Declare the test file
set(Tests
  disassembler_test)

# 2. Declare dependencies of each test file
set(disassembler_test_deps
  disassembler)

# 3. Add dependencies to a list, need to be in the same order as item 1
set(Dependencies
  disassembler_test_deps)


###################################################################

add_subdirectory(unity)
foreach(tst depen IN ZIP_LISTS Tests Dependencies)
  message(STATUS "test=${tst}, dependency=${depen}")
  add_executable(
    ${tst}
    ${tst}.c)

  target_link_libraries(
    ${tst}
    unity)

  foreach(ds ${depen})
    foreach(d ${${ds}})
      message(STATUS "-> test=${tst}, dependency=${d}")
      target_link_libraries(
        ${tst}
        ${d})
    endforeach(d)
  endforeach(ds)

  target_include_directories(
    ${tst} PUBLIC
    ${PROJECT_SOURCE_DIR}/test/unity)

  set_target_properties(
    ${tst}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}")

  add_test(${tst} "${TEST_OUTPUT_PATH}/${tst}")
endforeach()
