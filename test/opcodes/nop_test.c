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

void should_dont_change_anything(void) {
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_dont_change_anything);

    return UNITY_END();
}
