#include "unity.h"
#include "cpu.h"

struct BUS bus;
struct CPU cpu;

int stackEndAddress = 0x100;
char PLA = 0x68;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
  resetCpu(&cpu, &bus);
}

void tearDown(void) {
}

void should_pull_accumulator_from_the_stack(void) {
  writeBus(stackEndAddress + cpu.stack_pointer, 0x16, &bus);
  cpu.stack_pointer--;

  writeBus(0x600, PLA, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0xFD, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(0x16, cpu.accumulator);
}

void should_set_zero_flag_when_acc_equals_zero(void) {
  writeBus(stackEndAddress + cpu.stack_pointer, 0x00, &bus);
  cpu.stack_pointer--;

  writeBus(0x600, PLA, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0xFD, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}


void should_set_negative_flag_when_acc_equals_zero(void) {
  writeBus(stackEndAddress + cpu.stack_pointer, 0xf1, &bus);
  cpu.stack_pointer--;

  writeBus(0x600, PLA, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0xFD, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_zero_flag_when_acc_equals_zero(void) {
  writeBus(stackEndAddress + cpu.stack_pointer, 0x01, &bus);
  cpu.stack_pointer--;

  writeBus(0x600, PLA, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0xFD, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_negative_flag_when_acc_equals_zero(void) {
  writeBus(stackEndAddress + cpu.stack_pointer, 0x01, &bus);
  cpu.stack_pointer--;

  writeBus(0x600, PLA, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0xFD, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_pull_accumulator_from_the_stack);
    RUN_TEST(should_set_zero_flag_when_acc_equals_zero);
    RUN_TEST(should_set_negative_flag_when_acc_equals_zero);
    RUN_TEST(should_not_set_zero_flag_when_acc_equals_zero);
    RUN_TEST(should_not_set_negative_flag_when_acc_equals_zero);

    return UNITY_END();
}
