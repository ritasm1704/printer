#include <gtest/gtest.h>
#include "complex/complex.h"

TEST(PrinterTests, Creating) {
	Complex<int> testedObject(3, 3);
}

TEST(PrinterTests, CheckGetting) {
	Complex<int> testedObject(4, 3);
    ASSERT_EQ(testedObject.Re(), 4);
    ASSERT_EQ(testedObject.Im(), 3);
}
