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

void should_change_program_counter_with_a_new_location_when_zero_flag_is_not_true(void) {
  writeBus(0x600, 0xD0, &bus);
  writeBus(0x601, 0xff, &bus);

  // BNE - Branch if Not Equal (zero)
  cpu.status.zero = false;

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x600, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_change_program_counter_with_a_new_location_when_zero_flag_is_not_true);

    return UNITY_END();
}
