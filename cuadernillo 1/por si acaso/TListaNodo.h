#include <iostream>
#include "TComplejo.h"

using namespace std;

class TListaNodo{
    private:
        // El elemento del nodo
        TComplejo e;
        // El nodo anterior
        TListaNodo *anterior;
        // El nodo siguiente
        TListaNodo *siguiente;
    public:
        // Constructor por defecto
        TListaNodo ();
        // Constructor de copia
        TListaNodo (const TListaNodo &);
        // Destructor
        ~TListaNodo ();
        // Sobrecarga del operador asignación
        TListaNodo & operator=(const TListaNodo &);
};