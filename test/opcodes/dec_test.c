#include "unity.h"
#include "cpu.h"

struct BUS bus;
struct CPU cpu;

char DEC_ZeroPage  = 0xc6;
char DEC_ZeroPageX = 0xd6;
char DEC_Absolute  = 0xce;
char DEC_AbsoluteX = 0xde;

void setUp(void) {
  bus = initializeBus();
  writeBus(0xFFFC, 0x00, &bus);
  writeBus(0xFFFD, 0x06, &bus);
  resetCpu(&cpu, &bus);
}

void tearDown(void) {
}

void should_dec_1_to_the_zeropage_register(void) {
  writeBus(0xDD, 0x02, &bus);

  writeBus(0x600, DEC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(1, readBus(0xDD, &bus));
}

void should_set_zero_flag_when_zeropage_equals_zero(void){
  writeBus(0xDD, 0x01, &bus);

  writeBus(0x600, DEC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_zeropage_bit_7_is_set(void){
  writeBus(0xDD, 0xfe, &bus);

  writeBus(0x600, DEC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_negative_flag_when_zeropage_more_than_memory_value(void){
  writeBus(0xDD, 0x02, &bus);

  writeBus(0x600, DEC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_zero_flag_when_zeropage_less_then_memory_value(void){
  writeBus(0xDD, 0xfe, &bus);

  writeBus(0x600, DEC_ZeroPage, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_dec_1_to_the_zeropagex_register(void) {
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x02, &bus);

  writeBus(0x600, DEC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(1, readBus(0xDE, &bus));
}

void should_set_zero_flag_when_zeropagex_equals_zero(void){
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x01, &bus);

  writeBus(0x600, DEC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_zeropagex_bit_7_is_set(void){
  cpu.index_x = 0x01;
  writeBus(0xDE, 0xfd, &bus);

  writeBus(0x600, DEC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_negative_flag_when_zeropagex_more_than_memory_value(void){
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x02, &bus);

  writeBus(0x600, DEC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_zero_flag_when_zeropagex_less_then_memory_value(void){
  cpu.index_x = 0x01;
  writeBus(0xDE, 0x02, &bus);

  writeBus(0x600, DEC_ZeroPageX, &bus);
  writeBus(0x601, 0xDD, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_dec_1_to_the_absolute_register(void) {
  writeBus(0x4400, 0x02, &bus);

  writeBus(0x600, DEC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(1, readBus(0x4400, &bus));
}

void should_set_zero_flag_when_absolute_equals_zero(void){
  writeBus(0x4400, 0x01, &bus);

  writeBus(0x600, DEC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_absolute_bit_7_is_set(void){
  writeBus(0x4400, 0xfe, &bus);

  writeBus(0x600, DEC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_negative_flag_when_absolute_more_than_memory_value(void){
  writeBus(0x4400, 0x02, &bus);

  writeBus(0x600, DEC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_zero_flag_when_absolute_less_then_memory_value(void){
  writeBus(0x4400, 0xfe, &bus);

  writeBus(0x600, DEC_Absolute, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

void should_dec_1_to_the_absolutex_register(void) {
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x02, &bus);

  writeBus(0x600, DEC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(1, readBus(0x4401, &bus));
}

void should_set_zero_flag_when_absolutex_equals_zero(void){
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x01, &bus);

  writeBus(0x600, DEC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.zero);
}

void should_set_negative_flag_when_absolutex_bit_7_is_set(void){
  cpu.index_x = 0x01;
  writeBus(0x4401, 0xfe, &bus);

  writeBus(0x600, DEC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(true, cpu.status.negative);
}

void should_not_set_negative_flag_when_absolutex_more_than_memory_value(void){
  cpu.index_x = 0x01;
  writeBus(0x4401, 0x02, &bus);

  writeBus(0x600, DEC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.negative);
}

void should_not_set_zero_flag_when_absolutex_less_then_memory_value(void){
  cpu.index_x = 0x01;
  writeBus(0x4401, 0xfe, &bus);

  writeBus(0x600, DEC_AbsoluteX, &bus);
  writeBus(0x601, 0x00, &bus);
  writeBus(0x602, 0x44, &bus);

  clockCpu(&cpu, &bus);

  TEST_ASSERT_EQUAL(false, cpu.status.zero);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_dec_1_to_the_zeropage_register);
    RUN_TEST(should_set_zero_flag_when_zeropage_equals_zero);
    RUN_TEST(should_set_negative_flag_when_zeropage_bit_7_is_set);
    RUN_TEST(should_not_set_negative_flag_when_zeropage_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_zeropage_less_then_memory_value);

    RUN_TEST(should_dec_1_to_the_zeropagex_register);
    RUN_TEST(should_set_zero_flag_when_zeropagex_equals_zero);
    RUN_TEST(should_set_negative_flag_when_zeropagex_bit_7_is_set);
    RUN_TEST(should_not_set_negative_flag_when_zeropagex_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_zeropagex_less_then_memory_value);

    RUN_TEST(should_dec_1_to_the_absolute_register);
    RUN_TEST(should_set_zero_flag_when_absolute_equals_zero);
    RUN_TEST(should_set_negative_flag_when_absolute_bit_7_is_set);
    RUN_TEST(should_not_set_negative_flag_when_absolute_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_absolute_less_then_memory_value);

    RUN_TEST(should_dec_1_to_the_absolutex_register);
    RUN_TEST(should_set_zero_flag_when_absolutex_equals_zero);
    RUN_TEST(should_set_negative_flag_when_absolutex_bit_7_is_set);
    RUN_TEST(should_not_set_negative_flag_when_absolutex_more_than_memory_value);
    RUN_TEST(should_not_set_zero_flag_when_absolutex_less_then_memory_value);

    return UNITY_END();
}
