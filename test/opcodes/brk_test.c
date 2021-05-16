#include "unity.h"
#include "cpu.h"

char BRK = 0x00;

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

void should_break_the_loop(void) {
  cpu.status.carry = true;
  cpu.status.zero = true;
  cpu.status.interrupt = true;
  cpu.status.decimal = true;
  cpu.status.break_cmd = true;
  cpu.status.overflow = true;
  cpu.status.negative = true;
  writeBus(0xFFFE, 0x44, &bus);
  writeBus(0xFFFF, 0x00, &bus);

  writeBus(0x600, BRK, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x4400, cpu.pc);
  TEST_ASSERT_EQUAL_HEX(0xDF, readBus(STACK_END_ADDRESS + cpu.stack_pointer+1, &bus));
  TEST_ASSERT_EQUAL_HEX(0x02, readBus(STACK_END_ADDRESS + cpu.stack_pointer+2, &bus));
  TEST_ASSERT_EQUAL_HEX(0x06, readBus(STACK_END_ADDRESS + cpu.stack_pointer+3, &bus));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_break_the_loop);

    return UNITY_END();
}
