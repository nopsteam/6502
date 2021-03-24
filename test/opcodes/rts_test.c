#include "unity.h"
#include "cpu.h"

int stackEndAddress = 0x100; 
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
  writeBus(stackEndAddress + cpu.stack_pointer+1, 0x02, &bus);
  writeBus(stackEndAddress + cpu.stack_pointer+2, 0x06, &bus);

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
