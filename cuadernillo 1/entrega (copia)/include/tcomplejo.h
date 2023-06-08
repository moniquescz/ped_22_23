#ifndef tcomplejo_h
#define tcomplejo_h

#include <iostream>
using namespace std;

class TComplejo{
    private:
        double re;
        double im;
    public:
        TComplejo();
        TComplejo(double);
        TComplejo(double,double);
        TComplejo(const TComplejo&);
        ~TComplejo();
        TComplejo& operator= (const TComplejo&);
        TComplejo operator+ (const TComplejo&);
        TComplejo operator- (const TComplejo&);
        TComplejo operator* (const TComplejo&);
        TComplejo operator+ (double);
        TComplejo operator- (double);
        TComplejo operator* (double);
        bool operator== (const TComplejo&); // IGUALDAD de números complejos
        bool operator!= (const TComplejo&); // DESIGUALDAD de números complejos
        double Re(); // Devuelve PARTE REAL
        double Im(); // Devuelve PARTE IMAGINARIA
        void Re(double); // Modifica PARTE REAL
        void Im(double); // Modifica PARTE IMAGINARIA
        double Arg(void); // Calcula el Argumento (en Radianes)
        double Mod(void); // Calcula el Módulo
        friend ostream & operator<<(ostream &, const TComplejo &);
        friend TComplejo operator+ (double , const TComplejo&);
        friend TComplejo operator- (double , const TComplejo&);
        friend TComplejo operator* (double , const TComplejo&);
};

#endif