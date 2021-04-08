#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "unity.h"
#include "constants.h"
#include "disassembler.h"

struct PROGRAM programLoaded = {
  .program = NULL,
  .lines = 0
};

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
  programLoaded.program = NULL;
  programLoaded.lines = 0;
}

void test_function_should_do_sanity_check(void) {
  TEST_ASSERT_NOT_EQUAL_HEX32(0x69, GetOpcode(0x71)->hex);
  TEST_ASSERT_EQUAL_HEX32(0x71, GetOpcode(0x71)->hex);
}

void test_function_should_GetOpcode_for_ADC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x69)->instruction->name, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x65)->instruction->name, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x75)->instruction->name, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6D)->instruction->name, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x7D)->instruction->name, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x79)->instruction->name, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x61)->instruction->name, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x71)->instruction->name, "ADC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x69)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x65)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x75)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x6D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x7D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x79)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x61)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x71)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_AND(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x29)->instruction->name, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x25)->instruction->name, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x35)->instruction->name, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2D)->instruction->name, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x3D)->instruction->name, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x39)->instruction->name, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x21)->instruction->name, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x31)->instruction->name, "AND");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x29)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x25)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x35)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x2D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x3D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x39)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x21)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x31)->addressing->length, 2);
}
 
void test_function_should_GetOpcode_for_ASL(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x0A)->instruction->name, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x06)->instruction->name, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x16)->instruction->name, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x0E)->instruction->name, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x1E)->instruction->name, "ASL");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x0A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x06)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x16)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x0E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x1E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_BCC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x90)->instruction->name, "BCC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x90)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BCS(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB0)->instruction->name, "BCS");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB0)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BEQ(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF0)->instruction->name, "BEQ");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xF0)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BIT(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x24)->instruction->name, "BIT");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2C)->instruction->name, "BIT");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x24)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x2C)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_BMI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x30)->instruction->name, "BMI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x30)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BNE(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD0)->instruction->name, "BNE");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xD0)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BPL(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x10)->instruction->name, "BPL");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x10)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BRK(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x00)->instruction->name, "BRK");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x00)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_BVC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x50)->instruction->name, "BVC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x50)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BVS(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x70)->instruction->name, "BVS");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x70)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_CLC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x18)->instruction->name, "CLC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x18)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CLD(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD8)->instruction->name, "CLD");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xD8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CLI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x58)->instruction->name, "CLI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x58)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CLV(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB8)->instruction->name, "CLV");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CMP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC9)->instruction->name, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC5)->instruction->name, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD5)->instruction->name, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCD)->instruction->name, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xDD)->instruction->name, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD9)->instruction->name, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC1)->instruction->name, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD1)->instruction->name, "CMP");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xC9)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xC5)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xD5)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xCD)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xDD)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xD9)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xC1)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xD1)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_CPX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE0)->instruction->name, "CPX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE4)->instruction->name, "CPX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xEC)->instruction->name, "CPX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xE0)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xE4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xEC)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_CPY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC0)->instruction->name, "CPY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC4)->instruction->name, "CPY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCC)->instruction->name, "CPY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xC0)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xC4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xCC)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_DEC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC6)->instruction->name, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD6)->instruction->name, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCE)->instruction->name, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xDE)->instruction->name, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCA)->instruction->name, "DEX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x88)->instruction->name, "DEY");
}

void test_function_should_GetOpcode_for_EOR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x49)->instruction->name, "EOR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x45)->instruction->name, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x55)->instruction->name, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4D)->instruction->name, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x5D)->instruction->name, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x59)->instruction->name, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x41)->instruction->name, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x51)->instruction->name, "EOR"); 

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x49)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x45)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x55)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x4D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x5D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x59)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x41)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x51)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_INC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE6)->instruction->name, "INC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF6)->instruction->name, "INC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xEE)->instruction->name, "INC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xFE)->instruction->name, "INC");
}

void test_function_should_GetOpcode_for_INX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE8)->instruction->name, "INX");
}

void test_function_should_GetOpcode_for_INY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC8)->instruction->name, "INY");
}

void test_function_should_GetOpcode_for_JMP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4C)->instruction->name, "JMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6C)->instruction->name, "JMP");
}

void test_function_should_GetOpcode_for_JSR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x20)->instruction->name, "JSR");
}

void test_function_should_GetOpcode_for_LDA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA9)->instruction->name, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA5)->instruction->name, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB5)->instruction->name, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAD)->instruction->name, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBD)->instruction->name, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB9)->instruction->name, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA1)->instruction->name, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB1)->instruction->name, "LDA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA9)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA5)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB5)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xAD)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xBD)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB9)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA1)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB1)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_LDX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA2)->instruction->name, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA6)->instruction->name, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB6)->instruction->name, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAE)->instruction->name, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBE)->instruction->name, "LDX"); 

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA2)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA6)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB6)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xAE)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xBE)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_LDY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA0)->instruction->name, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA4)->instruction->name, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB4)->instruction->name, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAC)->instruction->name, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBC)->instruction->name, "LDY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA0)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xAC)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xBC)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_LSR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4A)->instruction->name, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x46)->instruction->name, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x56)->instruction->name, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4E)->instruction->name, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x5E)->instruction->name, "LSR");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x4A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x46)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x56)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x4E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x5E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_NOP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xEA)->instruction->name, "NOP");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xEA)->addressing->length, 1);
} 

void test_function_should_GetOpcode_for_ORA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x09)->instruction->name, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x05)->instruction->name, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x15)->instruction->name, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x0D)->instruction->name, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x1D)->instruction->name, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x19)->instruction->name, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x01)->instruction->name, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x11)->instruction->name, "ORA"); 

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x09)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x05)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x15)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x0D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x1D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x19)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x01)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x11)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_PHA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x48)->instruction->name, "PHA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x48)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_PHP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x08)->instruction->name, "PHP");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x08)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_PLA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x68)->instruction->name, "PLA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x68)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_PLP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x28)->instruction->name, "PLP");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x28)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_ROL(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2A)->instruction->name, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x26)->instruction->name, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x36)->instruction->name, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2E)->instruction->name, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x3E)->instruction->name, "ROL");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x2A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x26)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x36)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x2E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x3E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_ROR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6A)->instruction->name, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x66)->instruction->name, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x76)->instruction->name, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6E)->instruction->name, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x7E)->instruction->name, "ROR"); 

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x6A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x66)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x76)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x6E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x7E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_RTI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x40)->instruction->name, "RTI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x40)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_RTS(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x60)->instruction->name, "RTS");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x60)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_SBC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE9)->instruction->name, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE5)->instruction->name, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF5)->instruction->name, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xED)->instruction->name, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xFD)->instruction->name, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF9)->instruction->name, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE1)->instruction->name, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF1)->instruction->name, "SBC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xE9)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xE5)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xF5)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xED)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xFD)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xF9)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xE1)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xF1)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_SEC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x38)->instruction->name, "SEC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x38)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_SED(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF8)->instruction->name, "SED");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xF8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_SEI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x78)->instruction->name, "SEI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x78)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_STA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x85)->instruction->name, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x95)->instruction->name, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8D)->instruction->name, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x9D)->instruction->name, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x99)->instruction->name, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x81)->instruction->name, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x91)->instruction->name, "STA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x85)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x95)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x9D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x99)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x81)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x91)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_STX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x86)->instruction->name, "STX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x96)->instruction->name, "STX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8E)->instruction->name, "STX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x86)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x96)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_STY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x84)->instruction->name, "STY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x94)->instruction->name, "STY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8C)->instruction->name, "STY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x84)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x94)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8C)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_TAX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAA)->instruction->name, "TAX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xAA)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TAY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA8)->instruction->name, "TAY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TSX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBA)->instruction->name, "TSX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xBA)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TXA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8A)->instruction->name, "TXA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8A)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TXS(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x9A)->instruction->name, "TXS");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x9A)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TYA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x98)->instruction->name, "TYA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x98)->addressing->length, 1);
}

void test_function_should_load_binary(void) {
  char* path = getenv("DATADIR");
  LoadBinary(path, &programLoaded);

  TEST_ASSERT_EQUAL(164, programLoaded.lines);

  free(programLoaded.program);
}

void test_function_should_exit_1_when_file_doenst_exist(void) {
  int exitCode = LoadBinary("./nothing", &programLoaded);
  TEST_ASSERT_EQUAL(1, exitCode);
}

void test_function_should_exit_1_when_path_doenst_exist(void) {
  int exitCode = LoadBinary("./nothing/nope", &programLoaded);
  TEST_ASSERT_EQUAL(1, exitCode);
}

void test_function_should_exit_1_when_file_cant_be_readed(void) {
  char * filename = "youcantreadthis";
  FILE * fptr;
  fptr = fopen(filename, "w");
  fclose(fptr);
  chmod(filename, 0x007);

  int exitCode = LoadBinary(filename, &programLoaded);
  TEST_ASSERT_EQUAL(1, exitCode);

  remove(filename);
}

void test_function_should_exit_1_when_no_file_provided(void) {
  int exitCode = LoadBinary("", &programLoaded);
  TEST_ASSERT_EQUAL(1, exitCode);
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_do_sanity_check);
    RUN_TEST(test_function_should_GetOpcode_for_ADC);
    RUN_TEST(test_function_should_GetOpcode_for_AND);
    RUN_TEST(test_function_should_GetOpcode_for_ASL);
    RUN_TEST(test_function_should_GetOpcode_for_BCC);
    RUN_TEST(test_function_should_GetOpcode_for_BCS);
    RUN_TEST(test_function_should_GetOpcode_for_BEQ);
    RUN_TEST(test_function_should_GetOpcode_for_BIT);
    RUN_TEST(test_function_should_GetOpcode_for_BMI);
    RUN_TEST(test_function_should_GetOpcode_for_BNE);
    RUN_TEST(test_function_should_GetOpcode_for_BPL);
    RUN_TEST(test_function_should_GetOpcode_for_BRK);
    RUN_TEST(test_function_should_GetOpcode_for_BVC);
    RUN_TEST(test_function_should_GetOpcode_for_BVS);
    RUN_TEST(test_function_should_GetOpcode_for_CLC);
    RUN_TEST(test_function_should_GetOpcode_for_CLD);
    RUN_TEST(test_function_should_GetOpcode_for_CLI);
    RUN_TEST(test_function_should_GetOpcode_for_CLV);
    RUN_TEST(test_function_should_GetOpcode_for_CMP);
    RUN_TEST(test_function_should_GetOpcode_for_CPX);
    RUN_TEST(test_function_should_GetOpcode_for_CPY);
    RUN_TEST(test_function_should_GetOpcode_for_DEC);
    RUN_TEST(test_function_should_GetOpcode_for_EOR);
    RUN_TEST(test_function_should_GetOpcode_for_INC);
    RUN_TEST(test_function_should_GetOpcode_for_INX);
    RUN_TEST(test_function_should_GetOpcode_for_INY);
    RUN_TEST(test_function_should_GetOpcode_for_JMP);
    RUN_TEST(test_function_should_GetOpcode_for_JSR);
    RUN_TEST(test_function_should_GetOpcode_for_LDA);
    RUN_TEST(test_function_should_GetOpcode_for_LDX);
    RUN_TEST(test_function_should_GetOpcode_for_LDY);
    RUN_TEST(test_function_should_GetOpcode_for_LSR);
    RUN_TEST(test_function_should_GetOpcode_for_NOP);
    RUN_TEST(test_function_should_GetOpcode_for_ORA);
    RUN_TEST(test_function_should_GetOpcode_for_PHA);
    RUN_TEST(test_function_should_GetOpcode_for_PHP);
    RUN_TEST(test_function_should_GetOpcode_for_PLA);
    RUN_TEST(test_function_should_GetOpcode_for_PLP);
    RUN_TEST(test_function_should_GetOpcode_for_ROL);
    RUN_TEST(test_function_should_GetOpcode_for_ROR);
    RUN_TEST(test_function_should_GetOpcode_for_RTI);
    RUN_TEST(test_function_should_GetOpcode_for_RTS);
    RUN_TEST(test_function_should_GetOpcode_for_SBC);
    RUN_TEST(test_function_should_GetOpcode_for_SEC);
    RUN_TEST(test_function_should_GetOpcode_for_SED);
    RUN_TEST(test_function_should_GetOpcode_for_SEI);
    RUN_TEST(test_function_should_GetOpcode_for_STA);
    RUN_TEST(test_function_should_GetOpcode_for_STX);
    RUN_TEST(test_function_should_GetOpcode_for_STY);
    RUN_TEST(test_function_should_GetOpcode_for_TAX);
    RUN_TEST(test_function_should_GetOpcode_for_TAY);
    RUN_TEST(test_function_should_GetOpcode_for_TSX);
    RUN_TEST(test_function_should_GetOpcode_for_TXA);
    RUN_TEST(test_function_should_GetOpcode_for_TXS);
    RUN_TEST(test_function_should_GetOpcode_for_TYA);
    RUN_TEST(test_function_should_load_binary);
    RUN_TEST(test_function_should_exit_1_when_no_file_provided);
    RUN_TEST(test_function_should_exit_1_when_file_doenst_exist);
    RUN_TEST(test_function_should_exit_1_when_path_doenst_exist);
    RUN_TEST(test_function_should_exit_1_when_file_cant_be_readed);

    return UNITY_END();
}
