#include "unity.h"
#include "cpu.h"

char LDY_Immediate = 0xa0;
char LDY_ZeroPage  = 0xa4;
char LDY_ZeroPageX = 0xb4;
char LDY_Absolute  = 0xac;
char LDY_AbsoluteX = 0xbc;

struct BUS bus;
struct CPU cpu;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
  resetCpu(&cpu, &bus);
}

void tearDown(void) {
}

void should_load_a_byte_of_memory_into_the_y_for_immediate(void) {
  writeBus(0x600, LDY_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.index_y);
}

void should_load_a_byte_of_memory_into_the_y_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDY_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.index_y);
}

void should_load_a_byte_of_memory_into_the_y_for_zeropage_y(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDY_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.index_y);
}

void should_load_a_byte_of_memory_into_the_y_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDY_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x1, cpu.index_y);
}

void should_load_a_byte_of_memory_into_the_y_for_absolute_x(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDY_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x1, cpu.index_y);
}

void should_set_zero_flag_when_y_equals_zero_value_for_immediate(void) {
  writeBus(0x600, LDY_Immediate, &bus);
  writeBus(0x601, 0x00, &bus);
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_y_equals_zero_value_for_zeropage(void) {
  writeBus(0xDD, 0x00, &bus); 

  writeBus(0x600, LDY_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_y_equals_zero_value_for_zeropage_y(void) {
  writeBus(0xDD, 0x00, &bus); 

  writeBus(0x600, LDY_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_y_equals_zero_value_for_absolute(void) {
  writeBus(0x4400, 0x00, &bus);

  writeBus(0x600, LDY_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_y_equals_zero_value_for_absolute_x(void) {
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, LDY_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_bit_7_is_set_for_immediate(void) {
  writeBus(0x600, LDY_Immediate, &bus);
  writeBus(0x601, 0xf1, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_zeropage(void) {
  writeBus(0xDD, 0xf1, &bus); 

  writeBus(0x600, LDY_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_zeropage_y(void) {
  writeBus(0xDD, 0xf1, &bus); 

  writeBus(0x600, LDY_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_absolute(void) {
  writeBus(0x4400, 0xf1, &bus);

  writeBus(0x600, LDY_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_absolute_x(void) {
  writeBus(0x4401, 0xf1, &bus);

  writeBus(0x600, LDY_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_zero_flag_when_y_more_than_memory_value_for_immediate(void) {
  writeBus(0x600, LDY_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_more_than_memory_value_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDY_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_more_than_memory_value_for_zeropage_y(void) {
  writeBus(0xDD, 0xf1, &bus); 

  writeBus(0x600, LDY_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_zero_flag_when_y_more_than_memory_value_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDY_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_more_than_memory_value_for_absolute_x(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDY_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_less_then_memory_value_for_immediate(void) {
  writeBus(0x600, LDY_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  cpu.index_y = 0x01;
  cpu.index_y = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_less_then_memory_value_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDY_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_y = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_less_then_memory_value_for_zeropage_y(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDY_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_y = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_less_then_memory_value_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDY_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_y_less_then_memory_value_for_absolute_x(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDY_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_immediate(void) {
  writeBus(0x600, LDY_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDY_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage_y(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDY_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDY_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute_x(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDY_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_load_a_byte_of_memory_into_the_y_for_immediate);
    RUN_TEST(should_load_a_byte_of_memory_into_the_y_for_zeropage);
    RUN_TEST(should_load_a_byte_of_memory_into_the_y_for_zeropage_y);
    RUN_TEST(should_load_a_byte_of_memory_into_the_y_for_absolute);
    RUN_TEST(should_load_a_byte_of_memory_into_the_y_for_absolute_x);

    RUN_TEST(should_set_zero_flag_when_y_equals_zero_value_for_immediate);
    RUN_TEST(should_set_zero_flag_when_y_equals_zero_value_for_zeropage);
    RUN_TEST(should_set_zero_flag_when_y_equals_zero_value_for_zeropage_y);
    RUN_TEST(should_set_zero_flag_when_y_equals_zero_value_for_absolute);
    RUN_TEST(should_set_zero_flag_when_y_equals_zero_value_for_absolute_x);

    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_immediate);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_zeropage);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_zeropage_y);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_absolute);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_absolute_x);

    RUN_TEST(should_not_set_zero_flag_when_y_more_than_memory_value_for_immediate);
    RUN_TEST(should_not_set_zero_flag_when_y_more_than_memory_value_for_zeropage);
    RUN_TEST(should_not_set_zero_flag_when_y_more_than_memory_value_for_zeropage_y);
    RUN_TEST(should_not_set_zero_flag_when_y_more_than_memory_value_for_absolute);
    RUN_TEST(should_not_set_zero_flag_when_y_more_than_memory_value_for_absolute_x);

    RUN_TEST(should_not_set_zero_flag_when_y_less_then_memory_value_for_immediate);
    RUN_TEST(should_not_set_zero_flag_when_y_less_then_memory_value_for_zeropage);
    RUN_TEST(should_not_set_zero_flag_when_y_less_then_memory_value_for_zeropage_y);
    RUN_TEST(should_not_set_zero_flag_when_y_less_then_memory_value_for_absolute);
    RUN_TEST(should_not_set_zero_flag_when_y_less_then_memory_value_for_absolute_x);

    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_immediate);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage_y);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute_x);

    return UNITY_END();
}
