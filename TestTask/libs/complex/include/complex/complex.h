#ifndef COMPLEX_H
#define COMPLEX_H

#include <math.h>

template<typename Type>

class Complex {

public:

    Complex(Type re = 0, Type im = 0) : re(re), im(im) {

    };

    ~Complex() {

    };

    const Type& getRe() const {
        return this->re;
    };

    Type& getRe() {
        return this->re;
    };

    const Type& getIm() const {
        return this->im;
    };

    Type& getIm(){
        return this->im;
    };

    double abs() {
        return sqrt(re * re + im * im);
    };

    

private:

    Type re;
    Type im;

};

#endif