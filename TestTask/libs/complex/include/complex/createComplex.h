#ifndef CREATECOMPLEX_H
#define CREATECOMPLEX_H

#include "complex/complex.h"

template<typename Type>
class CreateComplex {

public:
    virtual Complex<Type> createComplex(Type phase) = 0;

};

#endif