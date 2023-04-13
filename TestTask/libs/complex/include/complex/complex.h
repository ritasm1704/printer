#ifndef COMPLEX_H
#define COMPLEX_H

template<typename Type>

class Complex {

public:

    Complex(Type re, Type im) : re(re), im(im) {
    };

    ~Complex() {

    };

    const Type& Re() const {
        return this->re;
    };

    Type& Re() {
        return this->re;
    };

    const Type& Im() const {
        return this->im;
    };

    Type& Im(){
        return this->im;
    };

    

private:

    Type re;
    Type im;

};

#endif