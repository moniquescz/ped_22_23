#include <iostream>
#include "TListaPos.h"

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

class TListaCom{
    private:
        // Primer elemento de la lista
        TListaNodo *primero;
        // Ultimo elemento de la lista
        TListaNodo *ultimo;
    public:
                // Constructor por defecto
        TListaCom ();
        // Constructor de copia
        TListaCom (TListaCom &);
        // Destructor
        ~TListaCom ();
        // Sobrecarga del operador asignación
        TListaCom & operator=( TListaCom &);
        // Sobrecarga del operador igualdad
        bool operator==( TListaCom &);
        // Sobrecarga del operador desigualdad
        bool operator!=( TListaCom &);
        // Sobrecarga del operador suma
        TListaCom operator+(TListaCom &);
        // Sobrecarga del operador resta
        TListaCom operator-(TListaCom &);
        // Devuelve true si la lista está vacía, false en caso contrario
        bool EsVacia();
        // Inserta el elemento en la cabeza de la lista
        bool InsCabeza(TComplejo &);
        // Inserta el elemento a la izquierda de la posición indicada
        bool InsertarI(TComplejo &, TListaPos &);
        // Inserta el elemento a la derecha de la posición indicada
        bool InsertarD(TComplejo &, TListaPos &);
        // Busca y borra la primera ocurrencia del elemento
        bool Borrar(TComplejo &);
        // Busca y borra todas las ocurrencias del elemento
        bool BorrarTodos(TComplejo &);
        // Borra el elemento que ocupa la posición indicada
        bool Borrar(TListaPos &);
        // Obtiene el elemento que ocupa la posición indicada
        TComplejo Obtener(TListaPos &);
        // Devuelve true si el elemento está en la lista, false en caso contrario
        bool Buscar(TComplejo &);
        // Devuelve la longitud de la lista
        int Longitud();
        // Devuelve la primera posición en la lista
        TListaPos Primera();
        // Devuelve la última posición en la lista
        TListaPos Ultima();
        // Sobrecarga del operador salida
        friend ostream & operator<<(ostream &, TListaCom &);
};