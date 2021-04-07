#include "unity.h"
#include "cpu.h"

char CLI = 0x58;

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

void should_clear_flag(void) {
  cpu.status.interrupt = true;

  writeBus(0x600, CLI, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.interrupt);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_clear_flag);

    return UNITY_END();
}
