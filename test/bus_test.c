#include "unity.h"
#include "bus.h"

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

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_save_get_memory_data);

    return UNITY_END();
}
