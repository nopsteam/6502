# 1. Declare the test file
set(Tests
  asl_test
  bcc_test
  bcs_test
  beq_test
  bit_test
  bmi_test
  bne_test
  bpl_test
  bvc_test
  bvs_test
  clc_test
  cld_test
  cli_test
  clv_test
  cpx_test
  cpy_test
  dec_test
  dex_test
  dey_test
  inc_test
  inx_test
  iny_test
  jmp_test
  jsr_test
  lda_test
  ldx_test
  ldy_test
  lsr_test
  nop_test
  pha_test
  rol_test
  ror_test
  rti_test
  rts_test
  sec_test
  sed_test
  sei_test
  sta_test
  stx_test
  sty_test
  tax_test
  tay_test
  tsx_test
  txa_test
  txs_test
  tya_test)

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
