# 1. Declare the test file
set(Tests
  sta_test
  stx_test
  sty_test
  cpy_test
  inx_test
  iny_test
  lda_test
  ldx_test
  ldy_test
  nop_test
  pha_test
  txa_test
  bne_test)

###################################################################

foreach( tst ${Tests} )
  message(STATUS "test=${tst}")
  add_executable(
    ${tst}
    ${tst}.c)

  target_link_libraries(
    ${tst}
    unity
    cpu)

  target_include_directories(
    ${tst} PUBLIC
    ${PROJECT_SOURCE_DIR}/test/unity)

  set_target_properties(
    ${tst}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}")

  add_test(${tst} "${TEST_OUTPUT_PATH}/${tst}")
endforeach()
