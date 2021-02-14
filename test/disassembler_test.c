#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "constants.h"
#include "disassembler.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_should_do_sanity_check(void) {
  TEST_ASSERT_NOT_EQUAL_HEX32(0x69, GetOpcode(0x71)->hex);
  TEST_ASSERT_EQUAL_HEX32(0x71, GetOpcode(0x71)->hex);
}

void test_function_should_GetOpcode_for_ADC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x69)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x65)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x75)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6D)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x7D)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x79)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x61)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x71)->instruction, "ADC");

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
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x29)->instruction, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x25)->instruction, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x35)->instruction, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2D)->instruction, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x3D)->instruction, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x39)->instruction, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x21)->instruction, "AND");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x31)->instruction, "AND");

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
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x0A)->instruction, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x06)->instruction, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x16)->instruction, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x0E)->instruction, "ASL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x1E)->instruction, "ASL");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x0A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x06)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x16)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x0E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x1E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_BCC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x90)->instruction, "BCC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x90)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BCS(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB0)->instruction, "BCS");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB0)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BEQ(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF0)->instruction, "BEQ");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xF0)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BIT(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x24)->instruction, "BIT");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2C)->instruction, "BIT");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x24)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x2C)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_BMI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x30)->instruction, "BMI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x30)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BNE(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD0)->instruction, "BNE");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xD0)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BPL(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x10)->instruction, "BPL");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x10)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_BRK(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x00)->instruction, "BRK");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x00)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_BVC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x50)->instruction, "BVC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x70)->instruction, "BVC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x50)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x70)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_CLC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x18)->instruction, "CLC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x18)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CLD(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD8)->instruction, "CLD");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xD8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CLI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x58)->instruction, "CLI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x58)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CLV(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB8)->instruction, "CLV");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_CMP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC9)->instruction, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC5)->instruction, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD5)->instruction, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCD)->instruction, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xDD)->instruction, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD9)->instruction, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC1)->instruction, "CMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD1)->instruction, "CMP");

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
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE0)->instruction, "CPX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE4)->instruction, "CPX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xEC)->instruction, "CPX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xE0)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xE4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xEC)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_CPY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC0)->instruction, "CPY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC4)->instruction, "CPY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCC)->instruction, "CPY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xC0)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xC4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xCC)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_DEC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC6)->instruction, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xD6)->instruction, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCE)->instruction, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xDE)->instruction, "DEC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xCA)->instruction, "DEX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x88)->instruction, "DEY");
}

void test_function_should_GetOpcode_for_EOR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x49)->instruction, "EOR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x45)->instruction, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x55)->instruction, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4D)->instruction, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x5D)->instruction, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x59)->instruction, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x41)->instruction, "EOR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x51)->instruction, "EOR"); 

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
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE6)->instruction, "INC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF6)->instruction, "INC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xEE)->instruction, "INC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xFE)->instruction, "INC");
}

void test_function_should_GetOpcode_for_INX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE8)->instruction, "INX");
}

void test_function_should_GetOpcode_for_INY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xC8)->instruction, "INY");
}

void test_function_should_GetOpcode_for_JMP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4C)->instruction, "JMP");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6C)->instruction, "JMP");
}

void test_function_should_GetOpcode_for_JSR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x20)->instruction, "JSR");
}

void test_function_should_GetOpcode_for_LDA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA9)->instruction, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA5)->instruction, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB5)->instruction, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAD)->instruction, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBD)->instruction, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB9)->instruction, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA1)->instruction, "LDA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB1)->instruction, "LDA");

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
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA2)->instruction, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA6)->instruction, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB6)->instruction, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAE)->instruction, "LDX"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBE)->instruction, "LDX"); 

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA2)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA6)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB6)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xAE)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xBE)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_LDY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA0)->instruction, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA4)->instruction, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xB4)->instruction, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAC)->instruction, "LDY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBC)->instruction, "LDY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA0)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xB4)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xAC)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0xBC)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_LSR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4A)->instruction, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x46)->instruction, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x56)->instruction, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x4E)->instruction, "LSR");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x5E)->instruction, "LSR");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x4A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x46)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x56)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x4E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x5E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_NOP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xEA)->instruction, "NOP");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xEA)->addressing->length, 1);
} 

void test_function_should_GetOpcode_for_ORA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x09)->instruction, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x05)->instruction, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x15)->instruction, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x0D)->instruction, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x1D)->instruction, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x19)->instruction, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x01)->instruction, "ORA"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x11)->instruction, "ORA"); 

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
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x48)->instruction, "PHA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x48)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_PHP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x08)->instruction, "PHP");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x08)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_PLA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x68)->instruction, "PLA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x68)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_PLP(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x28)->instruction, "PLP");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x28)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_ROL(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2A)->instruction, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x26)->instruction, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x36)->instruction, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x2E)->instruction, "ROL");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x3E)->instruction, "ROL");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x2A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x26)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x36)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x2E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x3E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_ROR(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6A)->instruction, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x66)->instruction, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x76)->instruction, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6E)->instruction, "ROR"); 
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x7E)->instruction, "ROR"); 

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x6A)->addressing->length, 1);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x66)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x76)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x6E)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x7E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_RTI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x40)->instruction, "RTI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x40)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_RTS(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x60)->instruction, "RTS");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x60)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_SBC(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE9)->instruction, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE5)->instruction, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF5)->instruction, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xED)->instruction, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xFD)->instruction, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF9)->instruction, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xE1)->instruction, "SBC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF1)->instruction, "SBC");

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
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x38)->instruction, "SEC");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x38)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_SED(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xF8)->instruction, "SED");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xF8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_SEI(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x78)->instruction, "SEI");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x78)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_STA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x85)->instruction, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x95)->instruction, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8D)->instruction, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x9D)->instruction, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x99)->instruction, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x81)->instruction, "STA");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x91)->instruction, "STA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x85)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x95)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x9D)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x99)->addressing->length, 3);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x81)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x91)->addressing->length, 2);
}

void test_function_should_GetOpcode_for_STX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x86)->instruction, "STX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x96)->instruction, "STX");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8E)->instruction, "STX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x86)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x96)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8E)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_STY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x84)->instruction, "STY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x94)->instruction, "STY");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8C)->instruction, "STY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x84)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x94)->addressing->length, 2);
  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8C)->addressing->length, 3);
}

void test_function_should_GetOpcode_for_TAX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xAA)->instruction, "TAX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xAA)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TAY(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xA8)->instruction, "TAY");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xA8)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TSX(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0xBA)->instruction, "TSX");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0xBA)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TXA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x8A)->instruction, "TXA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x8A)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TXS(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x9A)->instruction, "TXS");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x9A)->addressing->length, 1);
}

void test_function_should_GetOpcode_for_TYA(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x98)->instruction, "TYA");

  TEST_ASSERT_EQUAL_INT(GetOpcode(0x98)->addressing->length, 1);
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_do_sanity_check, 1);
    RUN_TEST(test_function_should_GetOpcode_for_ADC, 2);
    RUN_TEST(test_function_should_GetOpcode_for_AND, 3);
    RUN_TEST(test_function_should_GetOpcode_for_ASL, 4);
    RUN_TEST(test_function_should_GetOpcode_for_BCC, 5);
    RUN_TEST(test_function_should_GetOpcode_for_BCS, 6);
    RUN_TEST(test_function_should_GetOpcode_for_BEQ, 7);
    RUN_TEST(test_function_should_GetOpcode_for_BIT, 8);
    RUN_TEST(test_function_should_GetOpcode_for_BMI, 9);
    RUN_TEST(test_function_should_GetOpcode_for_BNE, 10);
    RUN_TEST(test_function_should_GetOpcode_for_BPL, 11);
    RUN_TEST(test_function_should_GetOpcode_for_BRK, 12);
    RUN_TEST(test_function_should_GetOpcode_for_BVC, 12);
    RUN_TEST(test_function_should_GetOpcode_for_CLC, 13);
    RUN_TEST(test_function_should_GetOpcode_for_CLD, 14);
    RUN_TEST(test_function_should_GetOpcode_for_CLI, 15);
    RUN_TEST(test_function_should_GetOpcode_for_CLV, 16);
    RUN_TEST(test_function_should_GetOpcode_for_CMP, 17);
    RUN_TEST(test_function_should_GetOpcode_for_CPX, 18);
    RUN_TEST(test_function_should_GetOpcode_for_CPY, 19);
    RUN_TEST(test_function_should_GetOpcode_for_DEC, 20);
    RUN_TEST(test_function_should_GetOpcode_for_EOR, 21);
    RUN_TEST(test_function_should_GetOpcode_for_INC, 22);
    RUN_TEST(test_function_should_GetOpcode_for_INX, 23);
    RUN_TEST(test_function_should_GetOpcode_for_INY, 24);
    RUN_TEST(test_function_should_GetOpcode_for_JMP, 25);
    RUN_TEST(test_function_should_GetOpcode_for_JSR, 26);
    RUN_TEST(test_function_should_GetOpcode_for_LDA, 27);
    RUN_TEST(test_function_should_GetOpcode_for_LDX, 28);
    RUN_TEST(test_function_should_GetOpcode_for_LDY, 29);
    RUN_TEST(test_function_should_GetOpcode_for_LSR, 30);
    RUN_TEST(test_function_should_GetOpcode_for_NOP, 31);
    RUN_TEST(test_function_should_GetOpcode_for_ORA, 32);
    RUN_TEST(test_function_should_GetOpcode_for_PHA, 33);
    RUN_TEST(test_function_should_GetOpcode_for_PHP, 34);
    RUN_TEST(test_function_should_GetOpcode_for_PLA, 35);
    RUN_TEST(test_function_should_GetOpcode_for_PLP, 36);
    RUN_TEST(test_function_should_GetOpcode_for_ROL, 37);
    RUN_TEST(test_function_should_GetOpcode_for_ROR, 38);
    RUN_TEST(test_function_should_GetOpcode_for_RTI, 39);
    RUN_TEST(test_function_should_GetOpcode_for_RTS, 40);
    RUN_TEST(test_function_should_GetOpcode_for_SBC, 41);
    RUN_TEST(test_function_should_GetOpcode_for_SEC, 42);
    RUN_TEST(test_function_should_GetOpcode_for_SED, 43);
    RUN_TEST(test_function_should_GetOpcode_for_SEI, 44);
    RUN_TEST(test_function_should_GetOpcode_for_STA, 45);
    RUN_TEST(test_function_should_GetOpcode_for_STX, 46);
    RUN_TEST(test_function_should_GetOpcode_for_STY, 47);
    RUN_TEST(test_function_should_GetOpcode_for_TAX, 48);
    RUN_TEST(test_function_should_GetOpcode_for_TAY, 49);
    RUN_TEST(test_function_should_GetOpcode_for_TSX, 50);
    RUN_TEST(test_function_should_GetOpcode_for_TXA, 51);
    RUN_TEST(test_function_should_GetOpcode_for_TXS, 52);
    RUN_TEST(test_function_should_GetOpcode_for_TYA, 53);

    return UNITY_END();
}
