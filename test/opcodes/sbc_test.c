#include "unity.h"
#include "cpu.h"

char SBC_Immediate = 0xE9;
char SBC_ZeroPage = 0xE5;
char SBC_ZeroPageX = 0xF5;
char SBC_Absolute = 0xED;
char SBC_AbsoluteX = 0xFD;
char SBC_AbsoluteY = 0xF9;
char SBC_IndirectX = 0xE1;
char SBC_IndirectY = 0xF1;

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

void should_set_carry_flag_Immediate() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;

  writeBus(0x600, SBC_Immediate, &bus);
  writeBus(0x601, 0xFF, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_carry_flag_ZeroPage() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;
  writeBus(0xDD, 0xFF, &bus); 

  writeBus(0x600, SBC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_carry_flag_ZeroPageX() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;
  cpu.index_x = 0x01;
  writeBus(0xDE, 0xFF, &bus);

  writeBus(0x600, SBC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_carry_flag_Absolute() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;
  writeBus(0x4400, 0xFF, &bus);

  writeBus(0x600, SBC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_carry_flag_AbsoluteX() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;
  cpu.index_x = 0x01;
  writeBus(0x4401, 0xFF, &bus);

  writeBus(0x600, SBC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_carry_flag_AbsoluteY() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;
  cpu.index_y = 0x01;
  writeBus(0x4401, 0xFF, &bus);

  writeBus(0x600, SBC_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_carry_flag_IndirectX() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;
  writeBus(0x22EE, 0xFF, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, SBC_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);
  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_carry_flag_IndirectY() {
  cpu.accumulator = 0x80;
  cpu.status.carry = 0x1;
  writeBus(0x22f0, 0xFF, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, SBC_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.status.carry);
}

void should_set_overflow_flag_Immediate() {
  cpu.accumulator = 0x80;

  writeBus(0x600, SBC_Immediate, &bus);
  writeBus(0x601, 0x0, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_overflow_flag_ZeroPage() {
  cpu.accumulator = 0x80;
  writeBus(0xDD, 0x0, &bus); 

  writeBus(0x600, SBC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_overflow_flag_ZeroPageX() {
  cpu.accumulator = 0x80;
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x0, &bus);

  writeBus(0x600, SBC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_overflow_flag_Absolute() {
  cpu.accumulator = 0x80;
  writeBus(0x4400, 0x0, &bus);

  writeBus(0x600, SBC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_overflow_flag_AbsoluteX() {
  cpu.accumulator = 0x80;
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x0, &bus);

  writeBus(0x600, SBC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_overflow_flag_AbsoluteY() {
  cpu.accumulator = 0x80;
  cpu.index_y = 0x01;
  writeBus(0x4401, 0x0, &bus);

  writeBus(0x600, SBC_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_overflow_flag_IndirectX() {
  cpu.accumulator = 0x80;
  writeBus(0x22EE, 0x0, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, SBC_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);
  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_overflow_flag_IndirectY() {
  cpu.accumulator = 0x80;
  writeBus(0x22f0, 0x0, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, SBC_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.overflow);
}

void should_set_zero_flag_Immediate() {
  cpu.accumulator = 0x01;

  writeBus(0x600, SBC_Immediate, &bus);
  writeBus(0x601, 0x00, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_ZeroPage() {
  cpu.accumulator = 0x01;
  writeBus(0xDD, 0x00, &bus); 

  writeBus(0x600, SBC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_ZeroPageX() {
  cpu.accumulator = 0x01;
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x00, &bus);

  writeBus(0x600, SBC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_Absolute() {
  cpu.accumulator = 0x01;
  writeBus(0x4400, 0x00, &bus);

  writeBus(0x600, SBC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_AbsoluteX() {
  cpu.accumulator = 0x01;
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, SBC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_AbsoluteY() {
  cpu.accumulator = 0x01;
  cpu.index_y = 0x01;
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, SBC_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}
void should_set_zero_flag_IndirectX() {
  cpu.accumulator = 0x01;
  writeBus(0x22EE, 0x00, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, SBC_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);
  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_zero_flag_IndirectY() {
  cpu.accumulator = 0x01;
  writeBus(0x22f0, 0x00, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, SBC_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.zero);
}

void should_set_negative_flag_Immediate() {
  cpu.accumulator = 0xFF;

  writeBus(0x600, SBC_Immediate, &bus);
  writeBus(0x601, 0x00, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_ZeroPage() {
  cpu.accumulator = 0xFF;
  writeBus(0xDD, 0x00, &bus); 

  writeBus(0x600, SBC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_ZeroPageX() {
  cpu.accumulator = 0xFF;
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x00, &bus);

  writeBus(0x600, SBC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_Absolute() {
  cpu.accumulator = 0xFF;
  writeBus(0x4400, 0x00, &bus);

  writeBus(0x600, SBC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_AbsoluteX() {
  cpu.accumulator = 0xFF;
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, SBC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_AbsoluteY() {
  cpu.accumulator = 0xFF;
  cpu.index_y = 0x01;
  writeBus(0x4401, 0x00, &bus);

  writeBus(0x600, SBC_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_IndirectX() {
  cpu.accumulator = 0xFF;
  writeBus(0x22EE, 0x00, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, SBC_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);
  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

void should_set_negative_flag_IndirectY() {
  cpu.accumulator = 0xFF;
  writeBus(0x22f0, 0x00, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, SBC_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL_HEX(0xFE, cpu.accumulator);
  TEST_ASSERT_EQUAL_HEX(0x01, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_set_carry_flag_Immediate);
    RUN_TEST(should_set_carry_flag_ZeroPage);
    RUN_TEST(should_set_carry_flag_ZeroPageX);
    RUN_TEST(should_set_carry_flag_Absolute);
    RUN_TEST(should_set_carry_flag_AbsoluteX);
    RUN_TEST(should_set_carry_flag_AbsoluteY);
    RUN_TEST(should_set_carry_flag_IndirectX);
    RUN_TEST(should_set_carry_flag_IndirectY);

    RUN_TEST(should_set_overflow_flag_Immediate);
    RUN_TEST(should_set_overflow_flag_ZeroPage);
    RUN_TEST(should_set_overflow_flag_ZeroPageX);
    RUN_TEST(should_set_overflow_flag_Absolute);
    RUN_TEST(should_set_overflow_flag_AbsoluteX);
    RUN_TEST(should_set_overflow_flag_AbsoluteY);
    RUN_TEST(should_set_overflow_flag_IndirectX);
    RUN_TEST(should_set_overflow_flag_IndirectY);

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
