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

void test_function_should_GetOpcode(void) {
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x69)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x65)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x75)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x6D)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x7D)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x79)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x61)->instruction, "ADC");
  TEST_ASSERT_EQUAL_STRING(GetOpcode(0x71)->instruction, "ADC");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_do_sanity_check, 1);
    RUN_TEST(test_function_should_GetOpcode, 2);
    return UNITY_END();
}
