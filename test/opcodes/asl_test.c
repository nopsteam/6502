#include "unity.h"
#include "cpu.h"

char ASL_Accumulator = 0x0a;
char ASL_ZeroPage    = 0x06;
char ASL_ZeroPageX   = 0x16;
char ASL_Absolute    = 0x0e;
char ASL_AbsoluteX   = 0x1e;

/*
;MODE           SYNTAX       HEX LEN TIM

;Accumulator   ASL A         $0A  1   2
LDA #$10
ASL A

;Zero Page     ASL $44       $06  2   5
LDA #$10
STA $44
ASL $44

;Zero Page,X   ASL $44,X     $16  2   6
LDA #$10
LDX #$05
STA $49
ASL $44,X

;Absolute      ASL $4400     $0E  3   6
LDA #$10
STA $4400
ASL $4400

;Absolute,X    ASL $4400,X   $1E  3   7
LDA #$80
LDX #$05
STA $4405
ASL $4400,X

;tests -> flag zero, flag negative, flag carry
*/

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

void should_asl_accumulator(void){
  cpu.accumulator = 0x10;

  writeBus(0x600, ASL_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x20, cpu.accumulator);
}

void should_asl_zero_page(void){
  writeBus(0x44, 0x10, &bus);

  writeBus(0x600, ASL_ZeroPage, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x20, readBus(0x44, &bus));
}

void should_asl_zero_page_x(void){
  writeBus(0x49, 0x10, &bus);
  cpu.index_x = 0x05;

  writeBus(0x600, ASL_ZeroPageX, &bus);
  writeBus(0x601, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x20, readBus(0x49, &bus));
}

void should_asl_absolute(void){
  writeBus(0x4400, 0x10, &bus);

  writeBus(0x600, ASL_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x20, readBus(0x4400, &bus));
}

void should_asl_absolute_x(void){
  writeBus(0x4401, 0x00, &bus);
  cpu.index_x = 0x01;

  writeBus(0x600, ASL_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x20, readBus(0x4401, &bus));
}

void should_asl_and_set_carry(void){
  cpu.accumulator = 0x80;

  writeBus(0x600, ASL_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_asl_and_set_negative(void){
  cpu.accumulator = 0x40;

  writeBus(0x600, ASL_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x80, cpu.accumulator);
  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_asl_and_set_zero(void){
  cpu.accumulator = 0x80;

  writeBus(0x600, ASL_Accumulator, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x00, cpu.accumulator);
  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_asl_accumulator);
    RUN_TEST(should_asl_zero_page);
    RUN_TEST(should_asl_zero_page_x);
    RUN_TEST(should_asl_absolute);
    RUN_TEST(should_asl_absolute_x);
    RUN_TEST(should_asl_and_set_carry);
    RUN_TEST(should_asl_and_set_negative);
    RUN_TEST(should_asl_and_set_zero);

    return UNITY_END();
}

