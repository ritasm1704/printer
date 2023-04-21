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

    Type abs() {
        return sqrt(re * re + im * im);
    };

    Type arg() {
        if (re > 0 && im > 0) {
            return atan(im / re);
        } else if (re < 0 && im > 0) {
            return atan(im / re) + M_PI;
        } else if (re < 0 && im < 0) {
            return atan(im / re) - M_PI;
        } else if (re > 0 && im < 0) {
            return atan(im / re);
        }
    }

    Type argDeg() {
        return arg() * 180 / M_PI;
    }

    Complex<Type> conj() {
        return Complex<Type>(re, -im);
    }

    

private:

    Type re;
    Type im;

};

#endif