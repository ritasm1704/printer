#include <gtest/gtest.h>
#include "complex/createComplexFromPhase.h"
#include "complex/createComplexFromPhaseDeg.h"

TEST(ComplexTests, Creating) {
    Complex<int> testedObject;
    Complex<int> testedObject2(1);
	Complex<int> testedObject3(2, 3);
}

TEST(ComplexTests, CheckGetting) {

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

TEST(ComplexTests, ChecAbs) {
	Complex<double> testedObject(2.0, 3.0);
    std::cout << "Re = " << testedObject.getRe() << " Im = " << testedObject.getIm() << std::endl;
    std::cout << "Abs = " << testedObject.abs() << std::endl;
}

TEST(ComplexTests, ChecArg) {
	Complex<double> testedObject(2.0, 3.0);
    std::cout << "Re = " << testedObject.getRe()<< " Im = " << testedObject.getIm() << std::endl;
    std::cout << "Arg = " << testedObject.arg() << std::endl;
    std::cout << "ArgDeg = " << testedObject.argDeg()<< std::endl;
}

TEST(ComplexTests, CheckConj) {
	Complex<int> testedObject(2, 3);
    Complex<int> testedObjectConj = testedObject.conj();
    ASSERT_EQ(testedObjectConj.getRe(), 2);
    ASSERT_EQ(testedObjectConj.getIm(), -3);
}

TEST(ComplexTests, CheckCreateComplexFromPhase) {

    CreateComplex<double>* createComplex = new CreateComplexFromPhase<double>();
	Complex<double> testedObject = createComplex->createComplex(0.9);
    std::cout << "Re = " << testedObject.getRe()<< " Im = " << testedObject.getIm() << std::endl;
    std::cout << "Arg = " << testedObject.arg() << std::endl;

    createComplex = new CreateComplexFromPhaseDeg<double>();
	testedObject = createComplex->createComplex(56.0);
    std::cout << "Re = " << testedObject.getRe()<< " Im = " << testedObject.getIm() << std::endl;
    std::cout << "ArgDeg = " << testedObject.argDeg()<< std::endl;
}
