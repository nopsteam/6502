#include "unity.h"
#include "cpu.h"

char RTS = 0x60;

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

void should_jump_back_to_sp_jsr_address(void) {
  writeBus(STACK_END_ADDRESS + cpu.stack_pointer, 0x06, &bus);
  cpu.stack_pointer--;
  writeBus(STACK_END_ADDRESS + cpu.stack_pointer, 0x02, &bus);
  cpu.stack_pointer--;

  writeBus(0x600, RTS, &bus);

  // RTS
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x0603, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_jump_back_to_sp_jsr_address);

    return UNITY_END();
}
