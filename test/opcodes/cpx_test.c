#include "unity.h"
#include "cpu.h"

struct BUS bus;
struct CPU cpu;

char CPX_Immediate = 0xE0;
char CPX_ZeroPage  = 0xE4;
char CPX_Absolute  = 0xEC;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
  resetCpu(&cpu, &bus);
}

void tearDown(void) {
}

void should_set_carry_flag_when_x_equal_than_memory_value_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  cpu.index_x = 0x01;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_x_more_than_memory_value_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_x_equal_than_memory_value_for_zeropage(void){
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x01;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_x_more_than_memory_value_for_zeropage(void){
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_x_equal_than_memory_value_for_absolute(void){
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x01;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_carry_flag_when_x_more_than_memory_value_for_absolute(void){
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.carry);
}

void should_set_zero_flag_when_x_equals_memory_value_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0x02, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_x_equals_memory_value_for_zeropage(void){
  writeBus(0xDD, 0x02, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_zero_flag_when_x_equals_memory_value_for_absolute(void){
  writeBus(0x4400, 0x02, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_bit_7_is_set_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0xff, &bus);

  cpu.index_x = 0x00;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_zeropage(void){
  writeBus(0xDD, 0xff, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x00;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_set_negative_flag_when_bit_7_is_set_for_absolute(void){
  writeBus(0x4400, 0xff, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x00;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_carry_flag_when_x_less_than_memory_value_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0xff, &bus);

  cpu.index_x = 0x00;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.carry);
}

void should_not_set_carry_flag_when_x_less_than_memory_value_for_zeropage(void){
  writeBus(0xDD, 0xff, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x00;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.carry);
}

void should_not_set_carry_flag_when_x_less_than_memory_value_for_absolute(void){
  writeBus(0x4400, 0x02, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x01;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.carry);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0xff, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_zeropage(void){
  writeBus(0xDD, 0xff, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_more_than_memory_value_for_absolute(void){
  writeBus(0x4400, 0xff, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0xff, &bus);

  cpu.index_x = 0x00;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_zeropage(void){
  writeBus(0xDD, 0xff, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x00;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_zero_flag_when_x_less_then_memory_value_for_absolute(void){
  writeBus(0x4400, 0x00, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0xff;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_immediate(void){
  writeBus(0x600, CPX_Immediate, &bus);
  writeBus(0x601, 0x01, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage(void){
  writeBus(0xDD, 0x01, &bus); 

  writeBus(0x600, CPX_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute(void){
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, CPX_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  cpu.index_x = 0x02;

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_set_carry_flag_when_x_equal_than_memory_value_for_immediate);
    RUN_TEST(should_set_carry_flag_when_x_more_than_memory_value_for_immediate);
    RUN_TEST(should_set_carry_flag_when_x_equal_than_memory_value_for_zeropage);
    RUN_TEST(should_set_carry_flag_when_x_more_than_memory_value_for_zeropage);
    RUN_TEST(should_set_carry_flag_when_x_equal_than_memory_value_for_absolute);
    RUN_TEST(should_set_carry_flag_when_x_more_than_memory_value_for_absolute);
    RUN_TEST(should_set_zero_flag_when_x_equals_memory_value_for_immediate);
    RUN_TEST(should_set_zero_flag_when_x_equals_memory_value_for_zeropage);
    RUN_TEST(should_set_zero_flag_when_x_equals_memory_value_for_absolute);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_immediate);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_zeropage);
    RUN_TEST(should_set_negative_flag_when_bit_7_is_set_for_absolute);
    RUN_TEST(should_not_set_carry_flag_when_x_less_than_memory_value_for_immediate);
    RUN_TEST(should_not_set_carry_flag_when_x_less_than_memory_value_for_zeropage);
    RUN_TEST(should_not_set_carry_flag_when_x_less_than_memory_value_for_absolute);
    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_immediate);
    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_zeropage);
    RUN_TEST(should_not_set_zero_flag_when_x_more_than_memory_value_for_absolute);
    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_immediate);
    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_zeropage);
    RUN_TEST(should_not_set_zero_flag_when_x_less_then_memory_value_for_absolute);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_immediate);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_zeropage);
    RUN_TEST(should_not_set_negative_flag_when_bit_7_is_not_set_for_absolute);

    return UNITY_END();
}
