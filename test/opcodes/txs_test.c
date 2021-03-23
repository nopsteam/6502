#include "unity.h"
#include "cpu.h"

char TXS_Implied = 0x9A;

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

void should_change_stack_pointer_address(void) {
  writeBus(0x600, TXS_Implied, &bus);

  cpu.index_x = 0x44;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x601, cpu.pc);
  TEST_ASSERT_EQUAL(0x00, cpu.index_y);
  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(0x44, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(false, cpu.status.break_cmd);
  TEST_ASSERT_EQUAL(false, cpu.status.carry);
  TEST_ASSERT_EQUAL(false, cpu.status.decimal);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
  TEST_ASSERT_EQUAL(false, cpu.status.interrupt);
  TEST_ASSERT_EQUAL(false, cpu.status.overflow);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_change_stack_pointer_address);

    return UNITY_END();
}
