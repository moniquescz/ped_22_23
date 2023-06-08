#ifndef tabbcom_h
#define tabbcom_h

#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"
#include <queue>
using namespace std;

class TNodoABB;

class TABBCom {
    friend class TNodoABB;
    private:
        TNodoABB *nodo;
        void InordenAux(TVectorCom &, int &) const;
        void PreordenAux(TVectorCom &, int &) const;
        void PostordenAux(TVectorCom &, int &) const;

        void Copiar(const TABBCom &);
        TComplejo Max();
    public:
        TABBCom();
        TABBCom(const TABBCom &);
        ~TABBCom();
        TABBCom & operator=(const TABBCom &);
        bool operator==(const TABBCom &) const;
        bool EsVacio() const;
        bool Insertar(const TComplejo &);
        bool Borrar(const TComplejo &);
        bool Buscar(const TComplejo &) const;
        TComplejo Raiz() const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;
        TVectorCom Inorden() const;
        TVectorCom Preorden() const;
        TVectorCom Postorden() const;
        TVectorCom Niveles() const;
        friend ostream & operator<<(ostream &, const TABBCom &);
};

class TNodoABB{
    friend class TABBCom;
    private:
        TComplejo item;
        TABBCom iz, de;
        void Copia(const TNodoABB &);
    public:
        TNodoABB();
        TNodoABB(const TNodoABB &);
        ~TNodoABB();
        TNodoABB & operator=(const TNodoABB &);
        bool esHoja() const;
};

#endif