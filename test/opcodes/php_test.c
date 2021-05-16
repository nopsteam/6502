#include "unity.h"
#include "cpu.h"

int stackEndAddress = 0x100;
char PHP = 0x08;
char PLP = 0x28;

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

void should_set_stack_with_status_flags(void) {
  cpu.status.carry = true;
  cpu.status.zero = true;
  cpu.status.interrupt = true;
  cpu.status.decimal = true;
  cpu.status.break_cmd = true;
  cpu.status.overflow = true;
  cpu.status.negative = true;

  writeBus(0x600, PHP, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xDF, readBus(STACK_END_ADDRESS + cpu.stack_pointer+1, &bus));
}

void should_set_status_flags_with_current_stack(void) {
  cpu.status.carry = true;
  cpu.status.zero = false;
  cpu.status.interrupt = true;
  cpu.status.decimal = false;
  cpu.status.break_cmd = false;
  cpu.status.overflow = false;
  cpu.status.negative = true;

  writeBus(0x600, PHP, &bus);
  writeBus(0x601, PLP, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.carry);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
  TEST_ASSERT_EQUAL(true, cpu.status.interrupt);
  TEST_ASSERT_EQUAL(false, cpu.status.decimal);
  TEST_ASSERT_EQUAL(false, cpu.status.break_cmd);
  TEST_ASSERT_EQUAL(false, cpu.status.overflow);
  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_set_stack_with_status_flags);
    RUN_TEST(should_set_status_flags_with_current_stack);

    return UNITY_END();
}
