#include "unity.h"
#include "cpu.h"

struct BUS bus;
struct CPU cpu;

char INY = 0xc8;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
  resetCpu(&cpu, &bus);
}

void tearDown(void) {
}

void should_add_1_to_the_Y_register(void) {
  writeBus(0x600, INY, &bus);
  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(2, cpu.index_y);
}

void should_set_zero_flag_when_Y_equals_zero(void){
  writeBus(0x600, INY, &bus);
  cpu.index_y = 0xff;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_bit_7_is_set(void){
  writeBus(0x600, INY, &bus);
  cpu.index_y = 0xfd;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_zero_flag_when_Y_more_than_memory_value(void){
  writeBus(0x600, INY, &bus);
  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_zero_flag_when_Y_less_then_memory_value(void){
  writeBus(0x600, INY, &bus);
  cpu.index_y = 0xfe;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_negative_flag_when_bit_7_is_not_set(void){
  writeBus(0x600, INY, &bus);
  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_add_1_to_the_Y_register);
    RUN_TEST(should_set_zero_flag_when_Y_equals_zero);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set);
    RUN_TEST(should_not_set_zero_flag_when_Y_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_Y_less_then_memory_value);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set);

    return UNITY_END();
}
