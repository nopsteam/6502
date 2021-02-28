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

void test_function_should_reset_cpu(void) {
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
  // STA Zero Page with pre loaded register: Accumulator=0xDD
  cpu.accumulator = 0xDD; 

  /* STA $0d */
  writeBus(0x600, 0x85, &bus);
  writeBus(0x601, 0x0D, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store Accumulator register on memory address 0x0D
  TEST_ASSERT_EQUAL(0xDD, readBus(0x0D, &bus));
}

void test_cpu_should_sta_zeropage_x(void) {
  // STA Zero Page X with pre loaded registers: Accumulator=0xDD and X=0x02
  cpu.accumulator = 0xDD;
  cpu.index_x = 0x02;

  /* STA $0d,X */
  writeBus(0x600, 0x95, &bus);
  writeBus(0x601, 0x0D, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store Accumulator register on memory address 0x0F
  TEST_ASSERT_EQUAL(0xDD, readBus(0x0F, &bus));
}

void test_cpu_should_sta_absolute(void) {
  // STA Absolute with pre loaded register: Accumulator=0xDD
  cpu.accumulator = 0xDD;

  /* STA $4400 */
  writeBus(0x600, 0x8d, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 3 times
  TEST_ASSERT_EQUAL(0x603, cpu.pc);
  // should store Accumulator register on memory address 0x4400
  TEST_ASSERT_EQUAL(cpu.accumulator, readBus(0x4400, &bus));
}

void test_cpu_should_sta_absolute_x(void) {
  // STA Absolute X with pre loaded register: Accumulator=0xDD and X=0x02
  cpu.accumulator = 0xDD;
  cpu.index_x = 0x02;

  /* STA $4400,X */
  writeBus(0x600, 0x9d, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 3 times
  TEST_ASSERT_EQUAL(0x603, cpu.pc);
  // should store Accumulator register on memory address 0x4402
  TEST_ASSERT_EQUAL(cpu.accumulator, readBus(0x4402, &bus));
}

void test_cpu_should_sta_absolute_y(void) {
  // STA Absolute Y with pre loaded register: Accumulator=0xDD and Y=0x02
  cpu.accumulator = 0xDD;
  cpu.index_y = 0x02;

  /* STA $4400,Y */
  writeBus(0x600, 0x99, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 3 times
  TEST_ASSERT_EQUAL(0x603, cpu.pc);
  // should store Accumulator register on memory address 0x4402
  TEST_ASSERT_EQUAL(cpu.accumulator, readBus(0x4402, &bus));
}

void test_cpu_should_sta_indirect_x(void) {
  // STA Indirect X with pre loaded register: Accumulator=0xDD and X=0x02
  cpu.accumulator = 0xDD;
  cpu.index_x = 0x02;
  // And pre loaded memory addresses: 0xF2=0xEE and 0xF3=0x22
  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  /* STA ($F0,X) */
  writeBus(0x600, 0x81, &bus);
  writeBus(0x601, 0xF0, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store Accumulator register on memory address 0x22EE
  TEST_ASSERT_EQUAL(cpu.accumulator, readBus(0x22EE, &bus));
}

void test_cpu_should_sta_indirect_y(void) {
  // STA Indirect Y with pre loaded register: Accumulator=0xDD and Y=0x02
  cpu.accumulator = 0xDD;
  cpu.index_y = 0x02;
  // And pre loaded memory addresses: 0xF0=0xEE and 0xF1=0x22
  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  /* STA ($F0),Y */
  writeBus(0x600, 0x91, &bus);
  writeBus(0x601, 0xF0, &bus);

  clockCpu(&cpu, &bus);

  // should move pc 2 times
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
  // should store Accumulator register on memory address 0x22F0
  TEST_ASSERT_EQUAL(cpu.accumulator, readBus(0x22F0, &bus));
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_reset_cpu);
    RUN_TEST(test_cpu_should_sta_zeropage);
    RUN_TEST(test_cpu_should_sta_zeropage_x);
    RUN_TEST(test_cpu_should_sta_absolute);
    RUN_TEST(test_cpu_should_sta_absolute_x);
    RUN_TEST(test_cpu_should_sta_absolute_y);
    RUN_TEST(test_cpu_should_sta_indirect_x);
    RUN_TEST(test_cpu_should_sta_indirect_y);

    return UNITY_END();
}
