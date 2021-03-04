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

void test_cpu_should_sty_zeropage(void) {
  // STY Zero Page with pre loaded register: Y=0xDD
  cpu.index_y = 0xDD;

  /* STY $0d */
  writeBus(0x600, 0x84, &bus);
  writeBus(0x601, 0x0D, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store Y register on memory address 0x0D
  TEST_ASSERT_EQUAL(0xDD, readBus(0x0D, &bus));
}

void test_cpu_should_sty_zeropage_x(void) {
  // STY Zero Page X with pre loaded registers: Y=0xDD and X=0x02
  cpu.index_y = 0xDD;
  cpu.index_x = 0x02;

  /* STY $0d,X */
  writeBus(0x600, 0x94, &bus);
  writeBus(0x601, 0x0D, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store Y register on memory address 0x0F
  TEST_ASSERT_EQUAL(0xDD, readBus(0x0F, &bus));
}

void test_cpu_should_sty_absolute(void) {
  // STY Absolute with pre loaded register: Y=0xDD
  cpu.index_y = 0xDD;

  /* STY $4400 */
  writeBus(0x600, 0x8C, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 3 times
  TEST_ASSERT_EQUAL(0x603, cpu.pc);
  // should store Y register on memory address 0x4400
  TEST_ASSERT_EQUAL(0xDD, readBus(0x4400, &bus));
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_cpu_should_sty_zeropage);
    RUN_TEST(test_cpu_should_sty_zeropage_x);
    RUN_TEST(test_cpu_should_sty_absolute);

    return UNITY_END();
}
