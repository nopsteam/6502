#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "disassembler.h"

struct PROGRAM_LINE prg[5];

void setUp(void) {
  prg[0].opcode = GetOpcode(0x4C);
  prg[0].args[0] = 0x07;
  prg[0].args[1] = 0x35;

  prg[1].opcode = GetOpcode(0xA0);
  prg[1].args[0] = 0x00;

  prg[2].opcode = GetOpcode(0xA5);
  prg[2].args[0] = 0xFE;

  prg[3].opcode = GetOpcode(0x91);
  prg[3].args[0] = 0x00;

  prg[4].opcode = GetOpcode(0x60);
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_should_do_return_asm(void) {
  TEST_ASSERT_EQUAL_STRING(toStringAsm(&prg[0]), "JMP $0735");
  TEST_ASSERT_EQUAL_STRING(toStringAsm(&prg[1]), "LDY #$00");
  TEST_ASSERT_EQUAL_STRING(toStringAsm(&prg[2]), "LDA $fe");
  TEST_ASSERT_EQUAL_STRING(toStringAsm(&prg[3]), "STA ($00),Y");
  TEST_ASSERT_EQUAL_STRING(toStringAsm(&prg[4]), "RTS ");
}

void test_function_should_do_return_hex(void) {
  TEST_ASSERT_EQUAL_STRING(toStringHex(&prg[0]), "4c 35 07");
  TEST_ASSERT_EQUAL_STRING(toStringHex(&prg[1]), "a0 00   ");
  TEST_ASSERT_EQUAL_STRING(toStringHex(&prg[2]), "a5 fe   ");
  TEST_ASSERT_EQUAL_STRING(toStringHex(&prg[3]), "91 00   ");
  TEST_ASSERT_EQUAL_STRING(toStringHex(&prg[4]), "60      ");
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_do_return_asm, 1);
    RUN_TEST(test_function_should_do_return_hex, 2);

    return UNITY_END();
}
