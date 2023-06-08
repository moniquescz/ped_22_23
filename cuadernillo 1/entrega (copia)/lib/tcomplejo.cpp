#include "tcomplejo.h"
#include <math.h>

TComplejo::TComplejo(){
    re = 0;
    im = 0;
};

TComplejo::TComplejo(double real){
    re=real;
    im=0;
};

TComplejo::TComplejo(double real, double imag){
    re=real;
    im=imag;
};

TComplejo::TComplejo(const TComplejo &t){
    re=t.re;
    im=t.im;
};

TComplejo::~TComplejo(){
    re=0;
    im=0;
};

TComplejo& TComplejo::operator= (const TComplejo &op2){
    if (this!=&op2){
        (*this).~TComplejo();
        re = op2.re;
        im = op2.im;
    }
    return *this;
};

TComplejo TComplejo::operator+ (const TComplejo &op2){
    TComplejo temp;
    temp.im = im + op2.im;
    temp.re = re + op2.re;
    return temp;
}

TComplejo TComplejo::operator- (const TComplejo &op2){
    TComplejo temp;
    temp.im = im - op2.im;
    temp.re = re - op2.re;
    return temp;
}

TComplejo TComplejo::operator* (const TComplejo &op2){
    TComplejo temp;
    temp.im = im * op2.im;
    temp.re = re * op2.re;
    return temp;
}

TComplejo TComplejo::operator+ (double d){
    TComplejo temp(d);
    TComplejo temp2;
    temp2.im = im + temp.im;
    temp2.re = re + temp.re;
    return temp2;
}

TComplejo TComplejo::operator- (double d){
    TComplejo temp(d);
    TComplejo temp2;
    temp2.im = im - temp.im;
    temp2.re = re - temp.re;
    return temp2;
}

TComplejo TComplejo::operator* (double d){
    TComplejo temp(d);
    TComplejo temp2;
    temp2.im = im * temp.im;
    temp2.re = re * temp.re;
    return temp2;
}

bool TComplejo::operator== (const TComplejo &op2){
    bool temp = false;
    if (op2.im==this->im && op2.re==this->re){
        temp = true;
    }
    return temp;
}

bool TComplejo::operator!= (const TComplejo &op2){
    bool temp = true;
    if (op2.im==this->im && op2.re==this->re){
        temp = false;
    }
    return temp;
}

double TComplejo::Re(){
    return this->re;
}

double TComplejo::Im(){
    return this->im;
}

void TComplejo::Re(double d){
    this->re = d;
}

void TComplejo::Im(double d){
    this->im = d;
}

double TComplejo::Arg(void){
    return atan2(im,re);
}

double TComplejo::Mod(void){
    double a = sqrt(pow(this->im,2)+pow(this->re,2));
    return a;
}

ostream& operator<<(ostream &s, const TComplejo &obj){
    s << "(" << obj.re << " ";
	s << obj.im << ")";
	return s;
}

TComplejo operator+ (double d, const TComplejo &op2){
    TComplejo temp = d + op2;
    return temp;
     
}

TComplejo operator- (double d, TComplejo &op2){
    TComplejo temp = op2 - d;
    return temp;
}

TComplejo operator* (double d, TComplejo& op2){
    TComplejo temp = d*op2;
    return temp;
}