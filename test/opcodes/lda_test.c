#include "unity.h"
#include "cpu.h"

char LDA_Immediate = 0xa9;
char LDA_ZeroPage  = 0xa5;
char LDA_ZeroPageX = 0xb5;
char LDA_Absolute  = 0xad;
char LDA_AbsoluteX = 0xbd;
char LDA_AbsoluteY = 0xb9;
char LDA_IndirectX = 0xa1;
char LDA_IndirectY = 0xb1;

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

void should_load_a_byte_of_memory_into_the_accumulator_for_immediate(void){
  writeBus(0x600, LDA_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.accumulator);
}

void should_load_a_byte_of_memory_into_the_accumulator_for_zeropage(void){
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDA_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.accumulator);
}

void should_load_a_byte_of_memory_into_the_accumulator_for_zeropage_x(void){
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, LDA_ZeroPageX, &bus);
  writeBus(0x601, 0xDC, &bus);

  cpu.index_x = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.accumulator);
}

void should_load_a_byte_of_memory_into_the_accumulator_for_absolute(void){
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, LDA_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x1, cpu.accumulator);
}

void should_load_a_byte_of_memory_into_the_accumulator_for_absolute_x(void){
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDA_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x1, cpu.accumulator);
}

void should_load_a_byte_of_memory_into_the_accumulator_for_absolute_y(void){
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, LDA_AbsoluteY, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_y = 0x01;
  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x1, cpu.accumulator);
}

void should_load_a_byte_of_memory_into_the_accumulator_for_indirect_x(void){
  writeBus(0x22EE, 0x01, &bus);

  writeBus(0xF2, 0xEE, &bus);
  writeBus(0xF3, 0x22, &bus);

  writeBus(0x600, LDA_IndirectX, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.accumulator);
}

void should_load_a_byte_of_memory_into_the_accumulator_for_indirect_y(void){
  writeBus(0x22f0, 0x01, &bus);

  writeBus(0xF0, 0xEE, &bus);
  writeBus(0xF1, 0x22, &bus);

  writeBus(0x600, LDA_IndirectY, &bus);
  writeBus(0x601, 0xF0, &bus);

  cpu.index_y = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(0x01, cpu.accumulator);
}




void should_set_zero_flag_when_accumulator_equals_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_set_negative_flag_when_bit_7_is_set(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_carry_flag_when_accumulator_less_than_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_zero_flag_when_accumulator_more_than_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_zero_flag_when_accumulator_less_then_memory_value(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

void should_not_set_negative_flag_when_bit_7_is_not_set(void){
  TEST_ASSERT_EQUAL(0x602, cpu.pc);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_immediate);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_zeropage);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_zeropage_x);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_absolute);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_absolute_x);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_absolute_y);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_indirect_x);
    RUN_TEST(should_load_a_byte_of_memory_into_the_accumulator_for_indirect_y);


    RUN_TEST(should_set_zero_flag_when_accumulator_equals_memory_value);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set);
    RUN_TEST(should_not_set_carry_flag_when_accumulator_less_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_accumulator_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_accumulator_less_then_memory_value);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set);



    return UNITY_END();
}
