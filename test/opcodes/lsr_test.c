#include "unity.h"
#include "cpu.h"

char LSR_Accumulator = 0x4a;
char LSR_ZeroPage    = 0x46;
char LSR_ZeroPageX   = 0x56;
char LSR_Absolute    = 0x4e;
char LSR_AbsoluteX   = 0x5e;

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

void should_lsr_accumulator(void){
  cpu.accumulator = 0x20;

  writeBus(0x600, LSR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x10, cpu.accumulator);
}

void should_lsr_zero_page(void){
  writeBus(0x44, 0x20, &bus);

  writeBus(0x600, LSR_ZeroPage, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x10, readBus(0x44, &bus));
}

void should_lsr_zero_page_x(void){
  writeBus(0x49, 0x20, &bus);
  cpu.index_x = 0x05;

  writeBus(0x600, LSR_ZeroPageX, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x10, readBus(0x49, &bus));
}

void should_lsr_absolute(void){
  writeBus(0x4400, 0x20, &bus);

  writeBus(0x600, LSR_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x10, readBus(0x4400, &bus));
}

void should_lsr_absolute_x(void){
  writeBus(0x4401, 0x20, &bus);
  cpu.index_x = 0x01;

  writeBus(0x600, LSR_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x10, readBus(0x4401, &bus));
}

void should_lsr_and_set_carry(void){
  cpu.accumulator = 0x01;

  writeBus(0x600, LSR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_lsr_and_set_negative(void){
  cpu.status.negative = true;
  cpu.accumulator = 0xFF;

  writeBus(0x600, LSR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x7f, cpu.accumulator);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_lsr_and_set_zero(void){
  cpu.accumulator = 0x01;

  writeBus(0x600, LSR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_lsr_accumulator);
    RUN_TEST(should_lsr_zero_page);
    RUN_TEST(should_lsr_zero_page_x);
    RUN_TEST(should_lsr_absolute);
    RUN_TEST(should_lsr_absolute_x);
    RUN_TEST(should_lsr_and_set_carry);
    RUN_TEST(should_lsr_and_set_negative);
    RUN_TEST(should_lsr_and_set_zero);

    return UNITY_END();
}

