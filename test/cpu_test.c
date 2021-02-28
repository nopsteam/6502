#include "unity.h"
#include "cpu.h"

struct BUS bus;
struct CPU cpu;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
}

void tearDown(void) {
}

void test_function_should_reset_cpu(void) {
  resetCpu(&cpu, &bus);
  TEST_ASSERT_EQUAL(0x0600, cpu.pc);
  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(0x00, cpu.index_x);
  TEST_ASSERT_EQUAL(0x00, cpu.index_y);
  TEST_ASSERT_EQUAL(0xFD, cpu.stack_pointer);
  TEST_ASSERT_EQUAL(false, cpu.status.carry);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
  TEST_ASSERT_EQUAL(false, cpu.status.interrupt);
  TEST_ASSERT_EQUAL(false, cpu.status.decimal);
  TEST_ASSERT_EQUAL(false, cpu.status.break_cmd);
  TEST_ASSERT_EQUAL(false, cpu.status.overflow);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void test_cpu_should_sta_zeropage(void) {
  // STA Zero Page with previusly loaded accumulator register 0xDD
  /* STA $0d */

  resetCpu(&cpu, &bus);
  cpu.accumulator = 0xDD; 

  // set STA Zero Page opcode instruction
  writeBus(0x600, 0x85, &bus);
  // set 0x0D at next byte to process
  writeBus(0x601, 0x0D, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store Accumulator register on memory address 0x0D
  TEST_ASSERT_EQUAL(0xDD, readBus(0x0D, &bus)); 
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_reset_cpu, 1);
    RUN_TEST(test_cpu_should_sta_zeropage, 2);

    return UNITY_END();
}
