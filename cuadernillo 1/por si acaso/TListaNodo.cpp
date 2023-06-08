#include "TListaNodo.h"

TListaNodo::TListaNodo(){
    this->e = TComplejo();
    this->anterior = NULL;
    this->siguiente = NULL;
}

TListaNodo::TListaNodo(const TListaNodo &obj){
    this->e = obj.e;
    this->anterior = obj.anterior;
    this->siguiente = obj.siguiente;
}

TListaNodo::~TListaNodo(){
    this->anterior = NULL;
    this->siguiente = NULL;
    this->e.~TComplejo();
}

TListaNodo& TListaNodo::operator=(const TListaNodo &obj){
    if (this!=&obj){
        this->e = obj.e;
        this->anterior = obj.anterior;
        this->siguiente = obj.siguiente;
    }
    return *this;
}