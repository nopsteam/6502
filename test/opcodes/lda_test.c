#include "unity.h"
#include "cpu.h"

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

void should_load_a_byte_of_memory_into_the_accumulator(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_set_zero_flag_when_accumulator_equals_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_set_negative_flag_when_bit_7_is_set(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_carry_flag_when_accumulator_less_than_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_zero_flag_when_accumulator_more_than_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_zero_flag_when_accumulator_less_then_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_negative_flag_when_bit_7_is_not_set(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    //RUN_TEST(test_cpu_should_sta_zeropage);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator);
    RUN_TEST(should_set_zero_flag_when_accumulator_equals_memory_value);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set);
    RUN_TEST(should_not_set_carry_flag_when_accumulator_less_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_accumulator_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_accumulator_less_then_memory_value);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set);



    return UNITY_END();
}
