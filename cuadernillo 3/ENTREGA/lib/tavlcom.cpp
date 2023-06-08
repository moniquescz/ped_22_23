#include "tavlcom.h"

// -------------------------- TNodoAVL --------------------------

TNodoAVL::TNodoAVL(){
    this->item = TComplejo();
    this->iz = TAVLCom();
    this->de = TAVLCom();
    this->fe = 0;
}

void TNodoAVL::Copia(const TNodoAVL &nodo){
    this->item = TComplejo(nodo.item);
    this->iz = TAVLCom(nodo.iz);
    this->de = TAVLCom(nodo.de);
    this->fe = nodo.fe;
}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo){
    this->Copia(nodo);
}

TNodoAVL::~TNodoAVL(){
    
}

TNodoAVL& TNodoAVL::operator=(const TNodoAVL &nodo){
    if (this!=&nodo){
        this->Copia(nodo);
    }
    return *this;
}

bool TNodoAVL::esHoja() const{
    if (this->iz.EsVacio() && this->de.EsVacio()){
        return true;
    }
    return false;
}


// -------------------------- TAVLCom --------------------------

TAVLCom::TAVLCom(){     //HECHO
    this->raiz = NULL;
}

void TAVLCom::Copia(const TAVLCom &arb){    //HECHO
    if (arb.raiz!=NULL){
        TNodoAVL *aux = new TNodoAVL();
        aux->item = arb.raiz->item;
        aux->iz.Copia(arb.raiz->iz);
        aux->de.Copia(arb.raiz->de);
        aux->fe = arb.raiz->fe;
        this->raiz = aux;
    }else{
        this->raiz = NULL;
    }
}

TAVLCom::TAVLCom(const TAVLCom &arb){   //HECHO
    this->Copia(arb);
}

TAVLCom::~TAVLCom(){    //HECHO
    if (this->raiz != NULL){
        delete this->raiz;
        this->raiz = NULL;
    }
}

TAVLCom& TAVLCom::operator=(const TAVLCom &arb){    //HECHO
    if (this != &arb){
        this->~TAVLCom();
        this->Copia(arb);
    }
    return *this;
}

bool TAVLCom::operator==(const TAVLCom &arb) const{  //HECHO
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

bool TAVLCom::operator!=(const TAVLCom &arb) const{  //HECHO
    return !(*this==arb);
}

bool TAVLCom::EsVacio() const{  //HECHO
    return (this->raiz == NULL);
}

TComplejo TAVLCom::Max(){ //HECHO
    TComplejo max = this->Raiz();
    if (!this->raiz->iz.EsVacio() && this->raiz->iz.Max() > max){
        max = this->raiz->iz.Max();
    }
    if (!this->raiz->de.EsVacio() && this->raiz->de.Max() > max){
        max = this->raiz->de.Max();
    }
    return max;
}

void TAVLCom::Mover(TNodoAVL* &j, TNodoAVL* &k){
    j = k;
    k = NULL;
}

void TAVLCom::EquilibrarIzquierda(){
    TNodoAVL* j;
    TNodoAVL* k;
    if (this->raiz->iz.raiz->fe == -1 || (this->raiz->iz.raiz->fe == 0 && this->raiz->fe == -1)){ //Rotación II
        //Mover (J, HijoIzq (I));
        Mover(j,this->raiz->iz.raiz);
        //Mover (HijoIzq (I), HijoDer(J));
        Mover(this->raiz->iz.raiz,j->de.raiz);
        //Mover (HijoDer (J), I);
        Mover(j->de.raiz,this->raiz);
        //FE (J) = 0; 
        j->fe = 0;
        //FE (HijoDer (J))=0;
        j->de.raiz->fe = 0;
        //Mover (I,J);
        Mover(this->raiz,j);
    }else{ //Rotación ID
        //Mover (J, HijoIzq (I));
        Mover(j,this->raiz->iz.raiz);
        //Mover (K, HijoDer (J));
        Mover(k,j->de.raiz);
        //E2 = FE (K);
        int E2 = k->fe;
        //Mover (HijoIzq (I), HijoDer(K));
        Mover(this->raiz->iz.raiz,k->de.raiz);
        //Mover (HijoDer (J), HijoIzq(K));
        Mover(j->de.raiz,k->iz.raiz);
        //Mover (HijoIzq (K), J);
        Mover(k->iz.raiz,j);
        //Mover (HijoDer (K), I);
        Mover(k->de.raiz, this->raiz);
        //FE (K) = 0;
        k->fe = 0;
        switch (E2)
        {
        case -1:
            k->iz.raiz->fe = 0;
            k->de.raiz->fe = 1;
            break;
        case 1:
            k->iz.raiz->fe = -1;
            k->de.raiz->fe = 0;
            break;
        case 0:
            k->iz.raiz->fe = 0;
            k->de.raiz->fe = 0;
            break;
        default:
            break; 
        }
        Mover(this->raiz,k);
    }
}

void TAVLCom::EquilibrarDerecha(){
    TNodoAVL* j;
    TNodoAVL* k;
    if (this->raiz->de.raiz->fe == 1 || (this->raiz->de.raiz->fe == 0 && this->raiz->fe == 1)){ //Rotación DD
        //Mover (J, HijoDer (I));
        Mover(j,this->raiz->de.raiz);
        //Mover (HijoDer (I), HijoIzq(J));
        Mover(this->raiz->de.raiz,j->iz.raiz);
        //Mover (HijoIzq (J), I);
        Mover(j->iz.raiz,this->raiz);
        //FE (J) = 0; 
        j->fe = 0;
        //FE (HijoDer (J))=0;
        j->iz.raiz->fe = 0;
        //Mover (I,J);
        Mover(this->raiz,j);
    }else{ //Rotación DI
        //Mover (J, HijoDer (I));
        Mover(j,this->raiz->de.raiz);
        //Mover (K, HijoIzq (J));
        Mover(k,j->iz.raiz);
        //E2 = FE (K);
        int E2 = k->fe;
        //Mover (HijoDer (I), HijoIzq(K));
        Mover(this->raiz->de.raiz,k->iz.raiz);
        //Mover (HijoIzq (J), HijoDer(K));
        Mover(j->iz.raiz,k->de.raiz);
        //Mover (HijoDer (K), J);
        Mover(k->de.raiz,j);
        //Mover (HijoIzq (K), I);
        Mover(k->iz.raiz, this->raiz);
        //FE (K) = 0;
        k->fe = 0;
        switch (E2)
        {
        case -1:
            k->iz.raiz->fe = 0;
            k->de.raiz->fe = 1;
            break;
        case 1:
            k->iz.raiz->fe = -1;
            k->de.raiz->fe = 0;
            break;
        case 0:
            k->iz.raiz->fe = 0;
            k->de.raiz->fe = 0;
            break;
        default:
            break;
        }
        Mover(this->raiz,k);
    }
}

void TAVLCom::equilibrarArbol(){
    if (!this->raiz->iz.EsVacio()){
        this->raiz->iz.equilibrarArbol();
    }
    if (!this->raiz->de.EsVacio()){
        this->raiz->de.equilibrarArbol();
    }
    if (this->raiz->fe == -2){
        EquilibrarIzquierda();
    }
    if (this->raiz->fe == 2){
        EquilibrarDerecha();
    }

}

int TAVLCom::calcularFe(){
    int feAux = 0;
    if (!this->EsVacio()){
        feAux = this->raiz->de.Altura() - this->raiz->iz.Altura();
    }
    return feAux;
}

void TAVLCom::actualizarFe(){
	if(!this->EsVacio()){
		this->raiz->fe = calcularFe();
		this->raiz->iz.actualizarFe();
		this->raiz->de.actualizarFe();
	}
}

bool TAVLCom::InsertarAux(const TComplejo &comp, bool &crece){
    bool creceHijoIz=false, creceHijoDe=false, doneOK=false;
    if (this->EsVacio()){
        this->raiz = new TNodoAVL();
        this->raiz->item = TComplejo(comp);
        doneOK = true;
        crece = true;
    }else{
        if (!this->Buscar(comp)){
            if (this->Raiz() > comp){
                doneOK = this->raiz->iz.InsertarAux(comp,creceHijoIz);
            }else{
                doneOK = this->raiz->de.InsertarAux(comp,creceHijoDe);
            }
            if (creceHijoIz || creceHijoDe){
                if ((creceHijoIz && this->raiz->fe==1) || (creceHijoDe && this->raiz->fe==-1)){
                    crece = false;
                    this->raiz->fe = 0;
                }else if (creceHijoIz && this->raiz->fe==0){
                    crece = true;
                    this->raiz->fe = -1;
                }else if (creceHijoDe && this->raiz->fe==0){
                    crece = true;
                    this->raiz->fe = 1;
                }else if (creceHijoIz && this->raiz->fe==-1){
                    //rotacion, fe = -2
                    EquilibrarIzquierda();
                    crece = false;
                }else if (creceHijoDe && this->raiz->fe==1){
                    //rotacion, fe = 2
                    EquilibrarDerecha();
                    crece = false;
                }
            }else{
                crece = false;
            }
        }
    }
    return doneOK;
}

bool TAVLCom::Insertar(const TComplejo &comp){
    bool crece = false;
    return InsertarAux(comp,crece);
}

bool TAVLCom::Borrar(const TComplejo &comp){
    bool decrece = false;
    return BorrarAux(comp,decrece);
}

bool TAVLCom::BorrarAux(const TComplejo &comp, bool &decrece){
    bool borrado = false, decreceHijoDe = false, decreceHijoIz = false;
    if (this->Buscar(comp)){
        if (this->Raiz() > comp){
            borrado = this->raiz->iz.BorrarAux(comp,decreceHijoIz);
        }else if (this->Raiz() < comp){
            borrado = this->raiz->de.BorrarAux(comp,decreceHijoDe);
        }else if (this->Raiz() == comp && this->raiz->de.EsVacio()){
            TAVLCom aux = *this;
            aux = this->raiz->iz;
            *this = aux;
            decrece = true;
            borrado = true;
            return borrado;
        }else if (this->Raiz() == comp && this->raiz->iz.EsVacio()){
            TAVLCom aux = *this;
            aux = this->raiz->de;
            *this = aux;
            decrece = true;
            borrado = true;
            return borrado;
        }else if (this->Raiz() == comp && !this->raiz->de.EsVacio() && !this->raiz->iz.EsVacio()){
            this->raiz->item = this->raiz->iz.Max();
            borrado = this->raiz->iz.BorrarAux(this->raiz->item, decreceHijoIz);
            if (this->raiz->fe == 2) {
                if (this->raiz->de.raiz->fe == 1 || this->raiz->de.raiz->fe == 0) {
                    EquilibrarDerecha();
                    this->raiz->fe = 0;
                    decrece = true;
                }
                else if (this->raiz->de.raiz->fe == -1) {
                    EquilibrarDerecha();
                    this->raiz->fe = 1;
                    decrece = true;
                }
            }else if (this->raiz->fe == -2) {
                if (this->raiz->iz.raiz->fe == -1 || this->raiz->iz.raiz->fe == 0) {
                    EquilibrarIzquierda();
                    this->raiz->fe = 0;
                    decrece = true;
                }
                else if (this->raiz->iz.raiz->fe == 1) {
                    EquilibrarIzquierda();
                    this->raiz->fe = -1;
                    decrece = true;
                }
            }
            decrece = true;
        }
        if ((decreceHijoIz || decreceHijoDe) && borrado){
            if ( (decreceHijoIz && this->raiz->fe==-1) || (decreceHijoDe && this->raiz->fe==1)){
                decrece = true;
                this->raiz->fe = 0;
            }else if (decreceHijoIz && this->raiz->fe==0){
                decrece = false;
                this->raiz->fe = 1;
            }else if (decreceHijoDe && this->raiz->fe==0){
                decrece = false;
                this->raiz->fe = -1;
            }else if (decreceHijoIz && this->raiz->fe==1){
                if(raiz->de.raiz->fe == 0){
                    EquilibrarDerecha();
                    decrece = false;
                    raiz->fe = -1;
                }else{
                    EquilibrarDerecha();
                    decrece = true;
                    raiz->fe = 0;
                }
                //rotacion, fe = 2
            }else if (decreceHijoDe && this->raiz->fe==-1){
                if(raiz->iz.raiz->fe == 0){
                    EquilibrarIzquierda();
                    decrece = false;
                    raiz->fe = 1;
                }else{
                    EquilibrarIzquierda();
                    decrece = true;
                    raiz->fe = 0;
                }
            }
        }else{
            decrece = false;
        }
    }
    return borrado;
}

bool TAVLCom::Buscar(const TComplejo &c) const{    //HECHO
    bool encontrado = false;
    if (!this->EsVacio()){
        if (this->raiz->item == c){
            encontrado = true;
        }else{
            encontrado = (this->raiz->iz.Buscar(c) || this->raiz->de.Buscar(c));
        }
    }
    return encontrado;
}

TComplejo TAVLCom::Raiz() const{    //HECHO
    TComplejo aux;
    if (!this->EsVacio()){
        aux = this->raiz->item;   
    }else{
        aux = TComplejo();
    }
    return aux;
}

int TAVLCom::Altura() const{    //HECHO
    int a1, a2;
    if (!this->EsVacio()){
        a1 = this->raiz->iz.Altura();
        a2 = this->raiz->de.Altura();
        return (1 + (a1 < a2 ? a2 : a1));
    }else{
        return 0;
    }
}

int TAVLCom::Nodos() const{    //HECHO
    int nodos = 0;
    if (!this->EsVacio()){
        nodos = 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
    }
    return nodos;
}

int TAVLCom::NodosHoja() const{    //HECHO
    int nodos = 0;
    if (!this->EsVacio()){
        if (this->raiz->esHoja() && this->raiz->esHoja()){
            nodos++;
        }else{
            nodos = this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
        }
    }
    return nodos;
}

void TAVLCom::InordenAux(TVectorCom &inord, int &posicion) const{    //HECHO
    if (!this->EsVacio()){
        if (this->raiz->iz.EsVacio() && this->raiz->de.EsVacio()){
            inord[posicion] = this->raiz->item;
            posicion++;
        }else{
            this->raiz->iz.InordenAux(inord,posicion);
            inord[posicion] = this->raiz->item;
            posicion++;
            this->raiz->de.InordenAux(inord,posicion);
        }
    }
}

void TAVLCom::PreordenAux(TVectorCom &preord, int &posicion) const{    //HECHO
    if (!this->EsVacio()){
        if (this->raiz->iz.EsVacio() && this->raiz->de.EsVacio()){
            preord[posicion] = this->raiz->item;
            posicion++;
        }else{
            preord[posicion] = this->raiz->item;
            posicion++;
            this->raiz->iz.PreordenAux(preord,posicion);
            this->raiz->de.PreordenAux(preord,posicion);
        }
    }
}

void TAVLCom::PostordenAux(TVectorCom &postord, int &posicion) const{    //HECHO
    if (!this->EsVacio()){
        if (this->raiz->iz.EsVacio() && this->raiz->de.EsVacio()){
            postord[posicion] = this->raiz->item;
            posicion++;
        }else{
            this->raiz->iz.PostordenAux(postord,posicion);
            this->raiz->de.PostordenAux(postord,posicion);
            postord[posicion] = this->raiz->item;
            posicion++;
        }

    }
}

TVectorCom TAVLCom::Inorden() const{    //HECHO
    TVectorCom inord(Nodos());
    int posicion = 1;
    InordenAux(inord,posicion);
    return inord;
}

TVectorCom TAVLCom::Preorden() const{    //HECHO
    TVectorCom preord(Nodos());
    int posicion = 1;
    PreordenAux(preord,posicion);
    return preord;
}

TVectorCom TAVLCom::Postorden() const{    //HECHO
    TVectorCom postord(Nodos());
    int posicion = 1;
    PostordenAux(postord,posicion);
    return postord;
}

ostream & operator<<(ostream &os, const TAVLCom &arb){    //HECHO
    os << arb.Inorden();
    return os;
}