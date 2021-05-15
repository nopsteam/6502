#include "unity.h"
#include "cpu.h"

char BEQ_Relative = 0xF0;

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
  writeBus(0x600, BEQ_Relative, &bus);
  writeBus(0x601, 0x0fe, &bus);

  // BEQ - Branch if Equal (zero)
  cpu.status.zero = true;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x600, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_change_program_counter_with_a_new_location_when_zero_flag_is_not_true);

    return UNITY_END();
}
