#ifndef CREATECOMPLEXFROMPHASEDEG_H
#define CREATECOMPLEXFROMPHASEDEG_H

#include "complex/createComplex.h"

template<typename Type>
class CreateComplexFromPhaseDeg : public CreateComplex<Type> {

public:
    Complex<Type> createComplex(Type phase) {
        std::cout << "Create complex from phase deg = " << phase << std::endl;
        phase = phase * M_PI / 180;
        return Complex<Type>(cos(phase), sin(phase));
    };
};

#endif