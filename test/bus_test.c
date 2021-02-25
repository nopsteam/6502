#include "unity.h"
#include "bus.h"

struct BUS bus;

void setUp(void) {
  bus = initialize();
}

void tearDown(void) {
}

void test_function_should_save_get_memory_data(void) {
  write(0x0000, 0x01, &bus);
  TEST_ASSERT_EQUAL(0x01, read(0x0000, &bus));
  TEST_ASSERT_EQUAL(0x01, bus.memory[0]);

  write(0x0100, 0x02, &bus);
  TEST_ASSERT_EQUAL(0x02, read(0x0100, &bus));
  TEST_ASSERT_EQUAL(0x02, bus.memory[256]);

  write(0x0600, 0x03, &bus);
  TEST_ASSERT_EQUAL(0x03, read(0x0600, &bus));
  TEST_ASSERT_EQUAL(0x03, bus.memory[1536]);

  write(0x0200, 0x04, &bus);
  TEST_ASSERT_EQUAL(0x04, read(0x0200, &bus));
  TEST_ASSERT_EQUAL(0x04, bus.display[0]);

  write(0x05FF, 0x05, &bus);
  TEST_ASSERT_EQUAL(0x05, read(0x05FF, &bus));
  TEST_ASSERT_EQUAL(0x05, bus.display[1023]);

  write(0x00FF, 0x06, &bus);
  TEST_ASSERT_EQUAL(0x06, read(0x00FF, &bus));
  TEST_ASSERT_EQUAL(0x06, bus.input);
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_save_get_memory_data, 1);

    return UNITY_END();
}
