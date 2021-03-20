#include "unity.h"
#include "cpu.h"

char LDX_Immediate = 0xa2;
char LDX_ZeroPage  = 0xa6;
char LDX_ZeroPageY = 0xb6;
char LDX_Absolute  = 0xae;
char LDX_AbsoluteY = 0xbe;

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

void should_load_a_byte_of_memory_into_the_x_for_immediate(void) {
  writeBus(0x600, LDX_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.index_x);
}

void should_load_a_byte_of_memory_into_the_x_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.index_x);
}

void should_load_a_byte_of_memory_into_the_x_for_zeropage_y(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDX_ZeroPageY, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.index_x);
}

void should_load_a_byte_of_memory_into_the_x_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x1, cpu.index_x);
}

void should_load_a_byte_of_memory_into_the_x_for_absolute_y(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDX_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x1, cpu.index_x);
}

void should_set_zero_flag_when_x_equals_zero_value_for_immediate(void) {
  writeBus(0x600, LDX_Immediate, &bus);
  writeBus(0x601, 0x00, &bus);
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_x_equals_zero_value_for_zeropage(void) {
  writeBus(0xDD, 0x00, &bus); 

  writeBus(0x600, LDX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_x_equals_zero_value_for_zeropage_y(void) {
  writeBus(0xDD, 0x00, &bus); 

  writeBus(0x600, LDX_ZeroPageY, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_x_equals_zero_value_for_absolute(void) {
  writeBus(0x4400, 0x00, &bus);

  writeBus(0x600, LDX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_x_equals_zero_value_for_absolute_y(void) {
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, LDX_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_bit_7_is_set_for_immediate(void) {
  writeBus(0x600, LDX_Immediate, &bus);
  writeBus(0x601, 0xf1, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_zeropage(void) {
  writeBus(0xDD, 0xf1, &bus); 

  writeBus(0x600, LDX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_zeropage_y(void) {
  writeBus(0xDD, 0xf1, &bus); 

  writeBus(0x600, LDX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_absolute(void) {
  writeBus(0x4400, 0xf1, &bus);

  writeBus(0x600, LDX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_absolute_y(void) {
  writeBus(0x4401, 0xf1, &bus);

  writeBus(0x600, LDX_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_immediate(void) {
  writeBus(0x600, LDX_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_zeropage_y(void) {
  writeBus(0xDD, 0xf1, &bus); 

  writeBus(0x600, LDX_ZeroPageY, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_absolute_y(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDX_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_immediate(void) {
  writeBus(0x600, LDX_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  cpu.index_x = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_zeropage_y(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDX_ZeroPageY, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_absolute_y(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDX_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  cpu.index_x = 0xff;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_immediate(void) {
  writeBus(0x600, LDX_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  cpu.index_x = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage_y(void) {
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDX_ZeroPageY, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute(void) {
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute_y(void) {
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDX_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_load_a_byte_of_memory_into_the_x_for_immediate);
    RUN_TEST(should_load_a_byte_of_memory_into_the_x_for_zeropage);
    RUN_TEST(should_load_a_byte_of_memory_into_the_x_for_zeropage_y);
    RUN_TEST(should_load_a_byte_of_memory_into_the_x_for_absolute);
    RUN_TEST(should_load_a_byte_of_memory_into_the_x_for_absolute_y);

    RUN_TEST(should_set_zero_flag_when_x_equals_zero_value_for_immediate);
    RUN_TEST(should_set_zero_flag_when_x_equals_zero_value_for_zeropage);
    RUN_TEST(should_set_zero_flag_when_x_equals_zero_value_for_zeropage_y);
    RUN_TEST(should_set_zero_flag_when_x_equals_zero_value_for_absolute);
    RUN_TEST(should_set_zero_flag_when_x_equals_zero_value_for_absolute_y);

    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_immediate);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_zeropage);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_zeropage_y);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_absolute);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_absolute_y);

    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_immediate);
    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_zeropage);
    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_zeropage_y);
    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_absolute);
    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_absolute_y);

    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_immediate);
    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_zeropage);
    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_zeropage_y);
    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_absolute);
    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_absolute_y);

    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_immediate);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage_y);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute_y);

    return UNITY_END();
}

