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

void test_cpu_should_stx_zeropage(void) {
  // STX Zero Page with pre loaded register: X=0xDD
  cpu.index_x = 0xDD;

  /* STX $0d */
  writeBus(0x600, 0x86, &bus);
  writeBus(0x601, 0x0D, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store X register on memory address 0x0D
  TEST_ASSERT_EQUAL(0xDD, readBus(0x0D, &bus));
}

void test_cpu_should_stx_zeropage_y(void) {
  // STX Zero Page Y with pre loaded registers: X=0xDD and Y=0x02
  cpu.index_x = 0xDD;
  cpu.index_y = 0x02;

  /* STX $0d,Y */
  writeBus(0x600, 0x96, &bus);
  writeBus(0x601, 0x0D, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store X register on memory address 0x0F
  TEST_ASSERT_EQUAL(0xDD, readBus(0x0F, &bus));
}

void test_cpu_should_stx_absolute(void) {
  // STX Absolute with pre loaded register: X=0xDD
  cpu.index_x = 0xDD;

  /* STX $4400 */
  writeBus(0x600, 0x8E, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 3 times
  TEST_ASSERT_EQUAL(0x603, cpu.pc);
  // should store X register on memory address 0x4400
  TEST_ASSERT_EQUAL(0xDD, readBus(0x4400, &bus));
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_cpu_should_stx_zeropage);
    RUN_TEST(test_cpu_should_stx_zeropage_y);
    RUN_TEST(test_cpu_should_stx_absolute);

    return UNITY_END();
}
