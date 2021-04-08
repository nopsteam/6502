#include <stdlib.h>
#include "unity.h"
#include "bus.h"
#include <sys/stat.h>

struct BUS bus;

void setUp(void) {
  bus = initializeBus();
}

void tearDown(void) {
}

void test_function_should_save_get_memory_data(void) {
  writeBus(0x0000, 0x01, &bus);
  TEST_ASSERT_EQUAL(0x01, readBus(0x0000, &bus));
  TEST_ASSERT_EQUAL(0x01, bus.memory[0]);

  writeBus(0x0100, 0x02, &bus);
  TEST_ASSERT_EQUAL(0x02, readBus(0x0100, &bus));
  TEST_ASSERT_EQUAL(0x02, bus.memory[256]);

  writeBus(0x0600, 0x03, &bus);
  TEST_ASSERT_EQUAL(0x03, readBus(0x0600, &bus));
  TEST_ASSERT_EQUAL(0x03, bus.memory[1536]);

  writeBus(0x0200, 0x04, &bus);
  TEST_ASSERT_EQUAL(0x04, readBus(0x0200, &bus));
  TEST_ASSERT_EQUAL(0x04, bus.display[0]);

  writeBus(0x05FF, 0x05, &bus);
  TEST_ASSERT_EQUAL(0x05, readBus(0x05FF, &bus));
  TEST_ASSERT_EQUAL(0x05, bus.display[1023]);

  writeBus(0x00FF, 0x06, &bus);
  TEST_ASSERT_EQUAL(0x06, readBus(0x00FF, &bus));
  TEST_ASSERT_EQUAL(0x06, bus.input);
}

void test_function_should_write_program_to_bus(void){
  char* path = getenv("DATADIR");
  writeProgramToBus(path, 0, &bus);
  TEST_ASSERT_EQUAL(0x60, readBus(0x0134, &bus));
  TEST_ASSERT_EQUAL(0x0, readBus(0x0135, &bus));
}

void test_function_should_exit_1_when_file_doenst_exist(void) {
  int exitCode = writeProgramToBus("./nothing", 0, &bus);
  TEST_ASSERT_EQUAL(1, exitCode);
}

void test_function_should_exit_1_when_path_doenst_exist(void) {
  int exitCode = writeProgramToBus("./nothing/nope", 0, &bus);
  TEST_ASSERT_EQUAL(1, exitCode);
}

void test_function_should_exit_1_when_file_cant_be_readed(void) {
  char * filename = "youcantreadthis";
  FILE * fptr;
  fptr = fopen(filename, "w");
  fclose(fptr);
  chmod(filename, 0x007);

  int exitCode = writeProgramToBus(filename, 0, &bus);
  TEST_ASSERT_EQUAL(1, exitCode);

  remove(filename);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_save_get_memory_data);
    RUN_TEST(test_function_should_write_program_to_bus);
    RUN_TEST(test_function_should_exit_1_when_file_doenst_exist);
    RUN_TEST(test_function_should_exit_1_when_path_doenst_exist);
    RUN_TEST(test_function_should_exit_1_when_file_cant_be_readed);

    return UNITY_END();
}
