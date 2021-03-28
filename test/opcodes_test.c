#include "unity.h"
#include "opcodes.h"

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

void test_function_should_do_binary_coded_decimal_conversion(void) {
  TEST_ASSERT_EQUAL(14, hexToDecimalMode(0x14));
  TEST_ASSERT_EQUAL(79, hexToDecimalMode(0x79));
  TEST_ASSERT_EQUAL(24, hexToDecimalMode(0x24));
  TEST_ASSERT_EQUAL(56, hexToDecimalMode(0x56));

  TEST_ASSERT_EQUAL(0,   hexToDecimalMode(0x00) + hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(79,  hexToDecimalMode(0x79) + hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(80,  hexToDecimalMode(0x24) + hexToDecimalMode(0x56));
  TEST_ASSERT_EQUAL(175, hexToDecimalMode(0x93) + hexToDecimalMode(0x82));
  TEST_ASSERT_EQUAL(165, hexToDecimalMode(0x89) + hexToDecimalMode(0x76));
  TEST_ASSERT_EQUAL(165, hexToDecimalMode(0x89) + hexToDecimalMode(0x76));
  TEST_ASSERT_EQUAL(140, hexToDecimalMode(0x80) + hexToDecimalMode(0xf0));
  TEST_ASSERT_EQUAL(141, hexToDecimalMode(0x80) + hexToDecimalMode(0xfa));
  TEST_ASSERT_EQUAL(72,  hexToDecimalMode(0x2f) + hexToDecimalMode(0x4f));
  TEST_ASSERT_EQUAL(66,  hexToDecimalMode(0x6f) + hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(0,   hexToDecimalMode(0x00) - hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(0,   hexToDecimalMode(0x00) - hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(-1,  hexToDecimalMode(0x00) - hexToDecimalMode(0x01));
  TEST_ASSERT_EQUAL(1,   hexToDecimalMode(0x0a) - hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(2,   hexToDecimalMode(0x0b) - hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(91,  hexToDecimalMode(0x9a) - hexToDecimalMode(0x00));
  TEST_ASSERT_EQUAL(92,  hexToDecimalMode(0x9b) - hexToDecimalMode(0x00));
}

typedef void (*Func)(void);

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_should_do_binary_coded_decimal_conversion);

    return UNITY_END();
}
