#include "tabbcom.h"
using namespace std;

// -------------------------- TNodoABB --------------------------

TNodoABB::TNodoABB(){
    this->item = TComplejo();
    this->iz = TABBCom();
    this->de = TABBCom();
}

void TNodoABB::Copia(const TNodoABB &nodo){
    this->item = TComplejo(nodo.item);
    this->de = TABBCom(nodo.de);
    this->iz = TABBCom(nodo.iz);
}

TNodoABB::TNodoABB(const TNodoABB &nodo){
    Copia(nodo);
}

TNodoABB::~TNodoABB(){
}

bool TNodoABB::esHoja() const{
    if (this->iz.EsVacio() && this->de.EsVacio()){
        return true;
    }
    return false;
}

TNodoABB& TNodoABB::operator=(const TNodoABB &nodo){
    if (this != &nodo){
        Copia(nodo);
    }
    return *this;
}

// -------------------------- TABBCom --------------------------

TABBCom::TABBCom(){     //HECHO
    this->nodo = NULL;
}

void TABBCom::Copiar(const TABBCom &arb){   //HECHO
    if (arb.nodo!=NULL){
        TNodoABB *aux = new TNodoABB();
        aux->item = arb.nodo->item;
        nodo = aux;
        nodo->iz.Copiar(arb.nodo->iz);
        nodo->de.Copiar(arb.nodo->de);
    }else{
        nodo = NULL;
    }
    
}

TABBCom::TABBCom(const TABBCom &arb){ //HECHO
    Copiar(arb);
}

TABBCom::~TABBCom(){ //HECHO
    if (nodo != NULL){
        delete nodo;
        nodo = NULL;
    }
}

TABBCom& TABBCom::operator=(const TABBCom &arb){ //HECHO
    if (this!=&arb){
        this->~TABBCom();
        Copiar(arb);
    }
    return *this;
}

bool TABBCom::operator==(const TABBCom &arb) const{     //HECHO
    bool iguales = true;
    TVectorCom elementosThis = this->Inorden();
    TVectorCom elementosArb = arb.Inorden();
    for (int i=1; i<=elementosThis.Tamano() && iguales;i++){
        if (!elementosThis.ExisteCom(elementosArb[i])){
            iguales = false;
        }
    }
    return iguales;
}

bool TABBCom::EsVacio() const{ //HECHO
    return (this->nodo == NULL);
}

bool TABBCom::Insertar(const TComplejo &comp){ //HECHO
    bool doneOK = false;
    if (this->EsVacio()){
        this->nodo = new TNodoABB();
        this->nodo->item = TComplejo(comp);
        doneOK = true;
    }else{
        if (!this->Buscar(comp)){
            if (this->Raiz() > comp){
                this->nodo->iz.Insertar(comp);
            }else{
                this->nodo->de.Insertar(comp);
            }
            doneOK = true;
        }
    }
    return doneOK;
}

TComplejo TABBCom::Max(){ //HECHO
    TComplejo max = this->Raiz();
    if (!this->nodo->iz.EsVacio() && this->nodo->iz.Max() > max){
        max = this->nodo->iz.Max();
    }
    if (!this->nodo->de.EsVacio() && this->nodo->de.Max() > max){
        max = this->nodo->de.Max();
    }
    return max;
}

bool TABBCom::Borrar(const TComplejo &comp){ //HECHO
    bool borrado = false;
    if (this->Buscar(comp)){
        if (this->Raiz() > comp){
            this->nodo->iz.Borrar(comp);
        }else if (this->Raiz() < comp){
            this->nodo->de.Borrar(comp);
        }else if (this->Raiz() == comp && this->nodo->de.EsVacio()){
            TABBCom aux = *this;
            aux = this->nodo->iz;
            *this = aux;
        }else if (this->Raiz() == comp && this->nodo->iz.EsVacio()){
            TABBCom aux = *this;
            aux = this->nodo->de;
            *this = aux;
        }else if (this->Raiz() == comp && !this->nodo->de.EsVacio() && !this->nodo->iz.EsVacio()){
            this->nodo->item = this->nodo->iz.Max();
            this->nodo->iz.Borrar(this->nodo->item);
        }
        borrado = true;
    }
    return borrado;
}

bool TABBCom::Buscar(const TComplejo &comp) const{ //HECHO
    bool encontrado = false;
    if (!this->EsVacio()){
        if (this->nodo->item == comp){
            encontrado = true;
        }else{
            encontrado = (this->nodo->iz.Buscar(comp) || this->nodo->de.Buscar(comp));
        }
    }
    return encontrado;
}

TComplejo TABBCom::Raiz() const{ //HECHO
    TComplejo aux;
    if (!this->EsVacio()){
        aux = nodo->item;
    }else{
        aux = TComplejo();
    }
    return aux;
}

int TABBCom::Altura() const{ //HECHO
    int a1, a2;
    if (!this->EsVacio()){
        a1 = this->nodo->iz.Altura();
        a2 = this->nodo->de.Altura();
        return (1 + (a1 < a2 ? a2 : a1));
    }else{
        return 0;
    }
}

int TABBCom::Nodos() const{ //HECHO
    int nodos = 0;
    if (!this->EsVacio()){
        nodos = 1 + this->nodo->iz.Nodos() + this->nodo->de.Nodos();
    }
    return nodos;
}

int TABBCom::NodosHoja() const{ //HECHO
    int nodos = 0;
    if (!this->EsVacio()){
        if (this->nodo->esHoja() && this->nodo->esHoja()){
            nodos++;
        }else{
            nodos = this->nodo->iz.NodosHoja() + this->nodo->de.NodosHoja();
        }
    }
    return nodos;
}

TVectorCom TABBCom::Inorden() const{ //HECHO
    TVectorCom inord(Nodos());
    int posicion = 1;
    InordenAux(inord,posicion);
    return inord;
}

TVectorCom TABBCom::Preorden() const{ //HECHO
    TVectorCom preord(Nodos());
    int posicion = 1;
    PreordenAux(preord,posicion);
    return preord;
}

TVectorCom TABBCom::Postorden() const{ //HECHO
    TVectorCom postord(Nodos());
    int posicion = 1;
    PostordenAux(postord,posicion);
    return postord;
}

TVectorCom TABBCom::Niveles() const{ //HECHO
    TVectorCom niv = TVectorCom(Nodos());
    int posicion = 1;
    queue<TABBCom> cola;
    cola.push(*this);
    while (!cola.empty()){
        TABBCom cabeza = cola.front();
        cola.pop();
        niv[posicion] = cabeza.nodo->item;
        posicion++;
        if (!cabeza.nodo->iz.EsVacio()){
            cola.push(cabeza.nodo->iz);
        }
        if (!cabeza.nodo->de.EsVacio()){
            cola.push(cabeza.nodo->de);
        }
    }
    return niv;
}


void TABBCom::InordenAux(TVectorCom &inord, int &posicion) const{ //HECHO
    if (!this->EsVacio()){
        if (this->nodo->iz.EsVacio() && this->nodo->de.EsVacio()){
            inord[posicion] = this->nodo->item;
            posicion++;
        }else{
            this->nodo->iz.InordenAux(inord,posicion);
            inord[posicion] = this->nodo->item;
            posicion++;
            this->nodo->de.InordenAux(inord,posicion);
        }

    }
}

void TABBCom::PreordenAux(TVectorCom &preord, int &posicion) const{ //HECHO
    if (!this->EsVacio()){
        if (this->nodo->iz.EsVacio() && this->nodo->de.EsVacio()){
            preord[posicion] = this->nodo->item;
            posicion++;
        }else{
            preord[posicion] = this->nodo->item;
            posicion++;
            this->nodo->iz.PreordenAux(preord,posicion);
            this->nodo->de.PreordenAux(preord,posicion);
        }

    }
}

void TABBCom::PostordenAux(TVectorCom &postord, int &posicion) const{ //HECHO
    if (!this->EsVacio()){
        if (this->nodo->iz.EsVacio() && this->nodo->de.EsVacio()){
            postord[posicion] = this->nodo->item;
            posicion++;
        }else{
            this->nodo->iz.PostordenAux(postord,posicion);
            this->nodo->de.PostordenAux(postord,posicion);
            postord[posicion] = this->nodo->item;
            posicion++;
        }

    }
}

ostream& operator<<(ostream &os, const TABBCom &arb){
    os << arb.Niveles();
    return os;
}

