#include "unity.h"
#include "cpu.h"

struct BUS bus;
struct CPU cpu;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
}

void tearDown(void) {
}

void test_function_should_reset_cpu(void) {
  resetCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(0x0600, cpu.pc);
  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(0x00, cpu.index_x);
  TEST_ASSERT_EQUAL(0x00, cpu.index_y);
  TEST_ASSERT_EQUAL(0xFD, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(false, cpu.status.carry);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
  TEST_ASSERT_EQUAL(false, cpu.status.interrupt);
  TEST_ASSERT_EQUAL(false, cpu.status.decimal);
  TEST_ASSERT_EQUAL(false, cpu.status.break_cmd);
  TEST_ASSERT_EQUAL(false, cpu.status.overflow);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_reset_cpu, 1);

    return UNITY_END();
}
