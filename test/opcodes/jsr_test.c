#include "unity.h"
#include "cpu.h"

char JSR = 0x20;

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

void should_jump_to_subrotine_program_counter_and_save_current_pc_on_stack(void) {
  writeBus(0x600, JSR, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  // JSR $4400
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x4400, cpu.pc);
  TEST_ASSERT_EQUAL(0x02, readBus(STACK_END_ADDRESS + cpu.stack_pointer+1, &bus));
  TEST_ASSERT_EQUAL(0x06, readBus(STACK_END_ADDRESS + cpu.stack_pointer+2, &bus));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_jump_to_subrotine_program_counter_and_save_current_pc_on_stack);

    return UNITY_END();
}
