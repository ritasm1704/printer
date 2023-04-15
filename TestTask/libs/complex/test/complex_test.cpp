#include <gtest/gtest.h>
#include "complex/complex.h"

TEST(PrinterTests, Creating) {
    Complex<int> testedObject;
    Complex<int> testedObject2(1);
	Complex<int> testedObject3(2, 3);
}

TEST(PrinterTests, CheckGetting) {

    Complex<int> testedObject1;
    ASSERT_EQ(testedObject1.getRe(), 0);
    ASSERT_EQ(testedObject1.getIm(), 0);

    Complex<int> testedObject2(1);
    ASSERT_EQ(testedObject2.getRe(), 1);
    ASSERT_EQ(testedObject2.getIm(), 0);

	Complex<int> testedObject3(2, 3);
    ASSERT_EQ(testedObject3.getRe(), 2);
    ASSERT_EQ(testedObject3.getIm(), 3);
}
