#include "unity.h"
#include "cpu.h"

char BIT_ZeroPage = 0x24;
char BIT_Absolute = 0x2C;

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

void bit_zp_should_set_NVZ_flag_as_true(void) {
  cpu.accumulator = 0x00;
  writeBus(0x44, 0xC0, &bus);

  // BIT $44
  writeBus(0x600, BIT_ZeroPage, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
  TEST_ASSERT_EQUAL(true, cpu.status.overflow);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void bit_zp_should_set_NVZ_flag_as_false(void) {
  cpu.accumulator = 0xFF; 
  writeBus(0x44, 0x3F, &bus);

  // BIT $44
  writeBus(0x600, BIT_ZeroPage, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
  TEST_ASSERT_EQUAL(false, cpu.status.overflow);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void bit_abs_should_set_NVZ_flag_as_true(void) {
  cpu.accumulator = 0x00; 
  writeBus(0x4400, 0xC0, &bus);

  // BIT $4400
  writeBus(0x600, BIT_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
  TEST_ASSERT_EQUAL(true, cpu.status.overflow);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void bit_abs_should_set_NVZ_flag_as_false(void) {
  cpu.accumulator = 0xFF; 
  writeBus(0x4400, 0x3F, &bus);

  // BIT $4400
  writeBus(0x600, BIT_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
  TEST_ASSERT_EQUAL(false, cpu.status.overflow);
  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(bit_zp_should_set_NVZ_flag_as_true);
    RUN_TEST(bit_zp_should_set_NVZ_flag_as_false);
    RUN_TEST(bit_abs_should_set_NVZ_flag_as_true);
    RUN_TEST(bit_abs_should_set_NVZ_flag_as_false);

    return UNITY_END();
}
