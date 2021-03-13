#include "unity.h"
#include "cpu.h"

struct BUS bus;
struct CPU cpu;

char CPY_Immediate = 0xC0;
char CPY_ZeroPage  = 0xC4;
char CPY_Absolute  = 0xCC;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
  resetCpu(&cpu, &bus);
}

void tearDown(void) {
}

void should_set_carry_flag_when_y_equal_than_memory_value_for_immediate(void){
  writeBus(0x600, CPY_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  // y > M
  cpu.index_y = 0x01;

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_y_more_than_memory_value_for_immediate(void){
  writeBus(0x600, CPY_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  // y > M
  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_y_equal_than_memory_value_for_zeropage(void){
  writeBus(0x600, CPY_ZeroPage, &bus);
  writeBus(0x601, 0x01, &bus);

  // y > M
  cpu.index_y = 0x01;

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_y_more_than_memory_value_for_zeropage(void){
  writeBus(0x600, CPY_ZeroPage, &bus);
  writeBus(0x601, 0x01, &bus);

  // y > M
  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_y_equal_than_memory_value_for_absolute(void){
  writeBus(0x600, CPY_Absolute, &bus);
  writeBus(0x601, 0x01, &bus);

  // y > M
  cpu.index_y = 0x01;

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_y_more_than_memory_value_for_absolute(void){
  writeBus(0x600, CPY_Absolute, &bus);
  writeBus(0x601, 0x01, &bus);

  // y > M
  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}


void should_set_zero_flag_when_y_equals_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_set_negative_flag_when_bit_7_is_set(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_carry_flag_when_y_less_than_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_zero_flag_when_y_more_than_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_zero_flag_when_y_less_then_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_negative_flag_when_bit_7_is_not_set(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_set_carry_flag_when_y_equal_than_memory_value_for_immediate);
    RUN_TEST(should_set_carry_flag_when_y_more_than_memory_value_for_immediate);
    RUN_TEST(should_set_carry_flag_when_y_equal_than_memory_value_for_zeropage);
    RUN_TEST(should_set_carry_flag_when_y_more_than_memory_value_for_zeropage);
    RUN_TEST(should_set_carry_flag_when_y_equal_than_memory_value_for_absolute);
    RUN_TEST(should_set_carry_flag_when_y_more_than_memory_value_for_absolute);

    RUN_TEST(should_set_zero_flag_when_y_equals_memory_value);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set);
    RUN_TEST(should_not_set_carry_flag_when_y_less_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_y_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_y_less_then_memory_value);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set);

    return UNITY_END();
}
