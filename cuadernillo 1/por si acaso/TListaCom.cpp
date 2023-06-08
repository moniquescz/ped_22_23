#include "tlistacom.h"

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
TListaPos::TListaPos(){
    this->pos = NULL;
}

TListaPos::TListaPos(const TListaPos &obj){
    this->pos = obj.pos;
}

TListaPos::~TListaPos(){
    this->pos = NULL;
}

TListaPos& TListaPos::operator=(const TListaPos &obj){
    if (this!=&obj){
        this->pos = obj.pos;
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos &obj){
    bool temp = false;
    if (this->pos==obj.pos){
        temp = true;
    }
    return temp;
}

bool TListaPos::operator!=(const TListaPos &obj){
    bool temp = true;
    if (this->pos==obj.pos){
        temp = false;
    }
    return temp;
}
//AQUI
/*
TListaPos TListaPos::Siguiente(){
    TListaPos temp = TListaPos();
    if (this->pos!=NULL){
        temp.pos = this->pos->siguiente;
    }
    return temp;
}

TListaPos TListaPos::Anterior(){
    TListaPos temp = TListaPos();
    if (this->pos!=NULL){
        temp.pos = this->pos->anterior;
    }
    return temp;
}*/

bool TListaPos::EsVacia(){
    bool temp = false;
    if (this->pos==NULL){
        temp = true;
    }
    return temp;
}

TListaCom::TListaCom(){
    this->primero = NULL;
    this->ultimo = NULL;
}