#include "unity.h"
#include "cpu.h"

char ROR_Accumulator = 0x6a;
char ROR_ZeroPage    = 0x66;
char ROR_ZeroPageX   = 0x76;
char ROR_Absolute    = 0x6e;
char ROR_AbsoluteX   = 0x7e;

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

void should_ror_accumulator(void){
  cpu.status.carry = true;
  cpu.accumulator = 0x02;

  writeBus(0x600, ROR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x81, cpu.accumulator);
}

void should_ror_zero_page(void){
  cpu.status.carry = true;
  writeBus(0x44, 0x02, &bus);

  writeBus(0x600, ROR_ZeroPage, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x81, readBus(0x44, &bus));
}

void should_ror_zero_page_x(void){
  cpu.status.carry = true;
  writeBus(0x49, 0x02, &bus);
  cpu.index_x = 0x05;

  writeBus(0x600, ROR_ZeroPageX, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x81, readBus(0x49, &bus));
}

void should_ror_absolute(void){
  cpu.status.carry = true;
  writeBus(0x4400, 0x02, &bus);

  writeBus(0x600, ROR_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x81, readBus(0x4400, &bus));
}

void should_ror_absolute_x(void){
  cpu.status.carry = true;
  writeBus(0x4401, 0x02, &bus);
  cpu.index_x = 0x01;

  writeBus(0x600, ROR_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x81, readBus(0x4401, &bus));
}

void should_ror_and_set_carry(void){
  cpu.accumulator = 0x01;

  writeBus(0x600, ROR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_ror_and_set_negative(void){
  cpu.status.negative = true;
  cpu.accumulator = 0xFF;

  writeBus(0x600, ROR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x7f, cpu.accumulator);
  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_ror_and_set_zero(void){
  cpu.accumulator = 0x01;

  writeBus(0x600, ROR_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_ror_accumulator);
    RUN_TEST(should_ror_zero_page);
    RUN_TEST(should_ror_zero_page_x);
    RUN_TEST(should_ror_absolute);
    RUN_TEST(should_ror_absolute_x);
    RUN_TEST(should_ror_and_set_carry);
    RUN_TEST(should_ror_and_set_negative);
    RUN_TEST(should_ror_and_set_zero);

    return UNITY_END();
}

