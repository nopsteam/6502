#include "unity.h"
#include "cpu.h"

char TAX_Implied = 0xAA;

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

void should_copy_index_x_to_accumulator_register(void){
  writeBus(0x600, TAX_Implied, &bus);
  cpu.accumulator = 0x22;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(0x22, cpu.index_x);
}

void should_set_zero_flag_when_acc_equals_memory_value(void){
  writeBus(0x600, TAX_Implied, &bus);
  cpu.accumulator = 0x00;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(0x00, cpu.index_x);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_bit_7_is_set(void){
  writeBus(0x600, TAX_Implied, &bus);
  cpu.accumulator = 0xff;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(0xff, cpu.index_x);
  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set(void){
  writeBus(0x600, TAX_Implied, &bus);
  cpu.accumulator = 0xa;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(0xa, cpu.index_x);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_copy_index_x_to_accumulator_register);
    RUN_TEST(should_set_zero_flag_when_acc_equals_memory_value);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set);

    return UNITY_END();
}
