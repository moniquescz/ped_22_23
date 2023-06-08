#include <iostream>
#include "TListaNodo.h"

using namespace std;

class TListaPos{
    private:
        // Puntero a un nodo de la lista
        TListaNodo *pos;
    public:
        // consttructor por defecto
        TListaPos ();
        // consttructor de copia
        TListaPos (const TListaPos &);
        // Destructor
        ~TListaPos ();
        // Sobrecarga del operador asignación
        TListaPos& operator=(const TListaPos &);
        // Sobrecarga del operador igualdad
        bool operator==(const TListaPos &);
        // Sobrecarga del operador desigualdad
        bool operator!=(const TListaPos &);
        // Devuelve la posición anterior
        TListaPos Anterior();
        // Devuelve la posición siguiente
        TListaPos Siguiente();
        // Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
        bool EsVacia();
};