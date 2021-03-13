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

void should_push_a_copy_of_accumulator_to_the_stack() {
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_push_a_copy_of_accumulator_to_the_stack);

    return UNITY_END();
}
