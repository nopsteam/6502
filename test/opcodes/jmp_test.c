#include "unity.h"
#include "cpu.h"

char JMP_Absolute = 0x4C;
char JMP_Indirect = 0x6C;

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

void should_jump_program_counter_with_a_new_absulute_location(void) {
  writeBus(0x600, JMP_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  // JMP $4400
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x4400, cpu.pc);
}

void should_jump_program_counter_with_a_new_indirect_location(void) {
  writeBus(0x4400, 0x00, &bus);
  writeBus(0x4401, 0x06, &bus);

  writeBus(0x600, JMP_Indirect, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  // JMP ($4400)
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x0600, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_jump_program_counter_with_a_new_absulute_location);

    return UNITY_END();
}
