#include "unity.h"
#include "cpu.h"

char EOR_Immediate = 0x49;
char EOR_ZeroPage = 0x45;
char EOR_ZeroPageX = 0x55;
char EOR_Absolute = 0x4D;
char EOR_AbsoluteX = 0x5D;
char EOR_AbsoluteY = 0x59;
char EOR_IndirectX = 0x41;
char EOR_IndirectY = 0x51;

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

void should_change_accumulator_with_logical_or_operation_when_Immediate() {
  cpu.accumulator = 0x00;

  writeBus(0x600, EOR_Immediate, &bus);
  writeBus(0x601, 0x11, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_change_accumulator_with_logical_or_operation_when_ZeroPage() {
  cpu.accumulator = 0x00;
  writeBus(0xDD, 0x11, &bus); 

  writeBus(0x600, EOR_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_change_accumulator_with_logical_or_operation_when_ZeroPageX() {
  cpu.accumulator = 0x00;
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x11, &bus);

  writeBus(0x600, EOR_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_change_accumulator_with_logical_or_operation_when_Absolute() {
  cpu.accumulator = 0x00;
  writeBus(0x4400, 0x11, &bus);

  writeBus(0x600, EOR_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_change_accumulator_with_logical_or_operation_when_AbsoluteX() {
  cpu.accumulator = 0x00;
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x11, &bus);

  writeBus(0x600, EOR_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_change_accumulator_with_logical_or_operation_when_AbsoluteY() {
  cpu.accumulator = 0x00;
  cpu.index_y = 0x01;
  writeBus(0x4401, 0x11, &bus);

  writeBus(0x600, EOR_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_change_accumulator_with_logical_or_operation_when_IndirectX() {
  cpu.accumulator = 0x00;
  writeBus(0x22EE, 0x11, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, EOR_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);
  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_change_accumulator_with_logical_or_operation_when_IndirectY() {
  cpu.accumulator = 0x00;
  writeBus(0x22f0, 0x11, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, EOR_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x11, cpu.accumulator);
}

void should_set_zero_flag_Immediate() {
  cpu.accumulator = 0x00;

  writeBus(0x600, EOR_Immediate, &bus);
  writeBus(0x601, 0x00, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_ZeroPage() {
  cpu.accumulator = 0x00;
  writeBus(0xDD, 0x00, &bus); 

  writeBus(0x600, EOR_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_ZeroPageX() {
  cpu.accumulator = 0x00;
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x00, &bus);

  writeBus(0x600, EOR_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_Absolute() {
  cpu.accumulator = 0x00;
  writeBus(0x4400, 0x00, &bus);

  writeBus(0x600, EOR_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_AbsoluteX() {
  cpu.accumulator = 0x00;
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, EOR_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_AbsoluteY() {
  cpu.accumulator = 0x00;
  cpu.index_y = 0x01;
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, EOR_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}
void should_set_zero_flag_IndirectX() {
  cpu.accumulator = 0x00;
  writeBus(0x22EE, 0x00, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, EOR_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);
  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_IndirectY() {
  cpu.accumulator = 0x00;
  writeBus(0x22f0, 0x00, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, EOR_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_negative_flag_Immediate() {
  cpu.accumulator = 0x00;

  writeBus(0x600, EOR_Immediate, &bus);
  writeBus(0x601, 0xFF, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_ZeroPage() {
  cpu.accumulator = 0x00;
  writeBus(0xDD, 0xFF, &bus); 

  writeBus(0x600, EOR_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_ZeroPageX() {
  cpu.accumulator = 0x00;
  cpu.index_x = 0x01;
  writeBus(0xDE, 0xFF, &bus);

  writeBus(0x600, EOR_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_Absolute() {
  cpu.accumulator = 0x00;
  writeBus(0x4400, 0xFF, &bus);

  writeBus(0x600, EOR_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_AbsoluteX() {
  cpu.accumulator = 0x00;
  cpu.index_x = 0x01;
  writeBus(0x4401, 0xFF, &bus);

  writeBus(0x600, EOR_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_AbsoluteY() {
  cpu.accumulator = 0x00;
  cpu.index_y = 0x01;
  writeBus(0x4401, 0xFF, &bus);

  writeBus(0x600, EOR_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_IndirectX() {
  cpu.accumulator = 0x00;
  writeBus(0x22EE, 0xFF, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, EOR_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);
  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_IndirectY() {
  cpu.accumulator = 0x00;
  writeBus(0x22f0, 0xFF, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, EOR_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFF, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_Immediate);
    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_ZeroPage);
    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_ZeroPageX);
    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_Absolute);
    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_AbsoluteX);
    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_AbsoluteY);
    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_IndirectX);
    RUN_TEST(should_change_accumulator_with_logical_or_operation_when_IndirectY);

    RUN_TEST(should_set_zero_flag_Immediate);
    RUN_TEST(should_set_zero_flag_ZeroPage);
    RUN_TEST(should_set_zero_flag_ZeroPageX);
    RUN_TEST(should_set_zero_flag_Absolute);
    RUN_TEST(should_set_zero_flag_AbsoluteX);
    RUN_TEST(should_set_zero_flag_AbsoluteY);
    RUN_TEST(should_set_zero_flag_IndirectX);
    RUN_TEST(should_set_zero_flag_IndirectY);

    RUN_TEST(should_set_negative_flag_Immediate);
    RUN_TEST(should_set_negative_flag_ZeroPage);
    RUN_TEST(should_set_negative_flag_ZeroPageX);
    RUN_TEST(should_set_negative_flag_Absolute);
    RUN_TEST(should_set_negative_flag_AbsoluteX);
    RUN_TEST(should_set_negative_flag_AbsoluteY);
    RUN_TEST(should_set_negative_flag_IndirectX);
    RUN_TEST(should_set_negative_flag_IndirectY);

    return UNITY_END();
}
