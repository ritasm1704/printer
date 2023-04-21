#ifndef CREATECOMPLEXFROMPHASE_H
#define CREATECOMPLEXFROMPHASE_H

#include "complex/createComplex.h"

template<typename Type>
class CreateComplexFromPhase : public CreateComplex<Type> {

public:
    Complex<Type> createComplex(Type phase) {
        std::cout << "Create complex from phase = " << phase << std::endl;
        return Complex<Type>(cos(phase), sin(phase));
    };
};

#endif