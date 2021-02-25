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
  TEST_ASSERT_EQUAL(read(0x0000, &bus), 0x0001);
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_save_get_memory_data, 1);

    return UNITY_END();
}
