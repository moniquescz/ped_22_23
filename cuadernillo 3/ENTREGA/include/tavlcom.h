#ifndef tavlcom_h
#define tavlcom_h

#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"
using namespace std;

class TNodoAVL;

class TAVLCom{
    friend class TNodoAVL;
    private:
        TNodoAVL *raiz;
        void Copia(const TAVLCom &);
        TComplejo Max();
        bool InsertarAux(const TComplejo &, bool &);
        bool BorrarAux(const TComplejo &, bool &);
        void EquilibrarIzquierda();
        void EquilibrarDerecha();
        int calcularFe();
        void equilibrarArbol();
        void actualizarFe();
        void Mover(TNodoAVL* &, TNodoAVL* &);
        void InordenAux(TVectorCom &, int &) const;
        void PreordenAux(TVectorCom &, int &) const;
        void PostordenAux(TVectorCom &, int &) const;
    public:
        TAVLCom();
        TAVLCom(const TAVLCom &);
        ~TAVLCom();
        TAVLCom & operator=(const TAVLCom &);
        bool operator==(const TAVLCom &) const;
        bool operator!=(const TAVLCom &) const;
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
        friend ostream & operator<<(ostream &, const TAVLCom &);
};

class TNodoAVL{
    friend class TAVLCom;
    private:
        TComplejo item;
        TAVLCom iz, de;
        int fe;
        void Copia(const TNodoAVL &);
        bool esHoja() const;
    public:
        TNodoAVL();
        TNodoAVL(const TNodoAVL &);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &);
};


#endif