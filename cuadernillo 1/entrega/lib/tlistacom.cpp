#include "tlistacom.h"

////////////////////////////////////////////////////////// TListaNodo
TListaNodo::TListaNodo(){
    this->e = TComplejo();
    this->anterior = NULL;
    this->siguiente = NULL;
}

TListaNodo::TListaNodo(const TListaNodo &obj){
    //this->e = obj.e;
    this->e = TComplejo(obj.e);
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
        this->~TListaNodo();
        this->e = obj.e;
        this->anterior = obj.anterior;
        this->siguiente = obj.siguiente;
    }
    return *this;
}



////////////////////////////////////////////////////////// TListaPos

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

TListaPos TListaPos::Siguiente(){
    /*
    TListaPos temp = TListaPos();
    if (this->pos!=NULL){
        temp.pos = this->pos->siguiente;
    }
    return temp;
    */
    TListaPos temp = TListaPos();
    if (!(this->EsVacia() || this->pos->siguiente==NULL)){
        temp.pos = this->pos->siguiente;
    }
    return temp;
}

TListaPos TListaPos::Anterior(){
    /*TListaPos temp = TListaPos();
    if (this->pos!=NULL){
        temp.pos = this->pos->anterior;
    }
    return temp;*/
    TListaPos temp = TListaPos();
    if (!(this->EsVacia() || this->pos->anterior==NULL)){
        temp.pos = this->pos-> anterior;
    }
    return temp;
}

bool TListaPos::EsVacia() const{
    bool temp = false;
    if (this->pos==NULL){
        temp = true;
    }
    return temp;
}



////////////////////////////////////////////////////////// TListaCom

TListaCom::TListaCom(){
    this->primero = NULL;
    this->ultimo = NULL;
}

void TListaCom::Copiar(const TListaCom &obj){
    TListaPos aux = obj.Ultima();
    this->primero = NULL;
    this->ultimo = NULL;
    if (!obj.EsVacia()){
        while(!aux.EsVacia()){
            bool insertado = false;
            TListaPos newNodo;
            newNodo.pos = new TListaNodo(*aux.pos);
            insertado = this->InsCabeza(newNodo.pos->e);
            if(insertado){
                aux = aux.Anterior();
            }
        }
    }
}

TListaCom::TListaCom(const TListaCom &obj){
    Copiar(obj);
}

TListaCom::~TListaCom (){
    TListaPos p,q;
    q=this->Primera();
    while(!q.EsVacia()){
        p=q;
        q=q.Siguiente();
        delete p.pos;
    }
    this->ultimo=NULL;
    this->primero=NULL;

}

TListaCom& TListaCom::operator=(const TListaCom &obj){
    if(*this!=obj){
        //TListaCom aux(obj);
        Copiar(obj);
    }
    return *this;
}

bool TListaCom::operator==(const TListaCom &lista){
    bool temp = true;
    if (this->Longitud()!=lista.Longitud()){
        temp = false;
    }else{
        TListaPos aux1,aux2;
        aux1 = this->Primera();
        aux2 = lista.Primera();
        while(!aux1.EsVacia()){
            if (aux1.pos->e!=aux2.pos->e){
                temp = false;
                break;
            }
            aux1 = aux1.Siguiente();
            aux2 = aux2.Siguiente();
        }
    }
    return temp;

}

bool TListaCom::operator!=(const TListaCom &lista){
    bool temp = false;
    if (this->Longitud()!=lista.Longitud()){
        temp = true;
    }
    return temp;
}

TListaCom TListaCom::operator+(const TListaCom &lista){
    if(this->EsVacia() && !lista.EsVacia()){
        TListaCom temp(lista);
        return temp;
    }else if(!this->EsVacia() && lista.EsVacia()){
        TListaCom temp(*this);
        return temp;
    }else{
        TListaCom temp(lista);
        TListaPos aux(this->Ultima());
        while(!aux.EsVacia()){
            temp.InsCabeza(aux.pos->e);
            aux = aux.Anterior();
        }
        return temp;
    }
}


TListaCom TListaCom::operator-(const TListaCom &lista){
    /*
    TListaCom temp = TListaCom(*this);
    TListaPos aux;
    aux = lista.Primera();
    while(!aux.EsVacia()){
        temp.Borrar(aux.pos->e);
        aux = aux.Siguiente();
    }
    return temp;*/
    if(this->EsVacia() && !lista.EsVacia()){
        TListaCom temp(lista);
        return temp;
    }else if(!this->EsVacia() && lista.EsVacia()){
        TListaCom temp(*this);
        return temp;
    }else{
        TListaCom temp(*this);
        TListaPos aux(lista.Primera());
        while(!aux.EsVacia()){
            bool b = temp.Borrar(aux.pos->e);
            if (!b) aux = aux.Siguiente();
        }
        return temp;
    }
}

bool TListaCom::EsVacia() const{
    bool esVacia = false;
    if (this->primero==NULL && this->ultimo==NULL)
        esVacia = true;
    return esVacia;
}

bool TListaCom::InsCabeza(const TComplejo &comp){
    bool todoOk = true;
    TListaPos aux;
    aux.pos = new TListaNodo();
    if(!aux.pos){
        todoOk = false;
        cerr << "ERROR: reservando memoria" << endl;
    }else{
        aux.pos->siguiente = this->primero;
        if (this->primero!=NULL){
            this->primero->anterior = aux.pos;
        }else{
            this->ultimo = aux.pos;
        }
        aux.pos->e = comp;
        this->primero = aux.pos;
    }
    return todoOk;
}

bool TListaCom::InsertarI(const TComplejo &com, const TListaPos &p){
    bool todoOk = true;
    if (p.EsVacia()){
        todoOk = false;
    }else if (this->primero==p.pos || this->Longitud()==1){
        todoOk = this->InsCabeza(com);
    }else{
        TListaPos aux;
        aux.pos = new TListaNodo();
        if(!aux.pos){
            todoOk = false;
            cerr << "ERROR: reservando memoria" << endl;
        }else{
            aux.pos->e = com;
            aux.pos->siguiente = p.pos;
            aux.pos->anterior = p.pos->anterior;
            p.pos->anterior->siguiente = aux.pos;
            p.pos->anterior = aux.pos;
        }
    }
    return todoOk;
}

bool TListaCom::InsertarD(const TComplejo &com, const TListaPos &p){
    try{
        bool todoOk = true;
        if (p.EsVacia()){
            todoOk = false;
        }else if (this->EsVacia()){
            //todoOk = this->InsCabeza(com);
            todoOk = false;
        }else{
            TListaPos aux;
            aux.pos = new TListaNodo();
            aux.pos->e = com;
            /*if(!aux.pos){
                todoOk = false;
                cerr << "ERROR: reservando memoria" << endl;
            }*/
            if(p.pos->siguiente==NULL){
                aux.pos->siguiente=NULL;
                aux.pos->anterior=this->ultimo;
                this->ultimo->siguiente=aux.pos;
                this->ultimo=aux.pos;
            }else{
                aux.pos->siguiente=p.pos->siguiente;
                aux.pos->anterior=p.pos;
                p.pos->siguiente->anterior=aux.pos;
                p.pos->siguiente=aux.pos;
            }
        }
        return todoOk;
    }catch(bad_alloc){
        return false;
    }
    
}

bool TListaCom::Borrar(const TComplejo &comp){
    if (!EsVacia() && Buscar(comp)) {
        TListaPos aux = Primera();
        if (Longitud() > 1) {
            if (aux.pos->e == comp) {
                TListaPos pos = aux.Siguiente();
                aux.pos->~TListaNodo();
                primero = pos.pos;
                pos.pos->anterior = NULL;
                return true;
            }
            while (!aux.Siguiente().EsVacia()) {
                aux.pos = aux.pos->siguiente;
                TListaPos auxUlt = Ultima();
                if (aux.pos->e == comp && aux == auxUlt) {
                    TListaPos pos = aux.Anterior();
                    aux.pos->~TListaNodo();
                    pos.pos->siguiente = NULL;
                    ultimo = pos.pos;
                    return true;
                }
                else {
                    if (aux.pos->e == comp) {
                        TListaPos p = aux.Anterior();
                        TListaPos q = aux.Siguiente();
                        aux.pos->~TListaNodo();
                        p.pos->siguiente = q.pos;
                        q.pos->anterior = p.pos;
                        return true;
                    }
                }
            }
        }
        else if (Longitud() == 1) {
            if (aux.pos->e == comp) {
                this->~TListaCom();
                return true;
            }
            else {
                return false;
            }
        }
    }

    return false;


    /*bool borrado = false;
    TListaPos aux;
    aux.pos=this->primero;
    while(!aux.EsVacia() && this->Buscar(comp)){
        if(aux.pos->e==comp){
            if (aux.Anterior().pos==NULL){
                aux.pos->siguiente->anterior=NULL;
            }else if (aux.Siguiente().pos==NULL){
                aux.pos->anterior->siguiente=NULL;
            }else{
                aux.pos->anterior->siguiente=aux.pos->siguiente;
                aux.pos->siguiente->anterior=aux.pos->anterior;
            }
            delete aux.pos;
            borrado = true;
        }
        aux.pos = aux.pos->siguiente;
    }
    return borrado;*/
}

bool TListaCom::BorrarTodos(const TComplejo &comp){
    bool todoOk = false;
    if(!this->EsVacia()){
        if(this->Buscar(comp)){
            do{
                this->Borrar(comp);
            }while(this->Buscar(comp));
            todoOk = true;
        }
    }
    return todoOk;
}

bool TListaCom::Borrar(TListaPos &p){
    bool todoOk = false;

    if (p.pos==NULL){
        return todoOk;
    }

    if(p.pos->siguiente==NULL){
        this->ultimo = p.pos->anterior;
        this->ultimo->siguiente = NULL;
    } else if(p.pos->anterior==NULL){
        this->primero = p.pos->siguiente;
        this->primero->anterior = NULL;
    }else{
        p.pos->anterior->siguiente = p.pos->siguiente;
        p.pos->siguiente->anterior = p.pos->anterior;
    }

    delete p.pos;
    return todoOk;
}

TComplejo TListaCom::Obtener(const TListaPos &p){
    TComplejo temp;
    if(!p.EsVacia()){
        temp = p.pos->e;
    }else{
        temp = TComplejo();
    }
    return temp;
}

bool TListaCom::Buscar(const TComplejo &comp){
    bool existe = false;
    TListaPos aux;
    aux.pos = this->primero;
    while(!aux.EsVacia() && !existe){
        if(aux.pos->e==comp){
            existe = true;
        }
        aux = aux.Siguiente();
    }
    return existe;
}

int TListaCom::Longitud() const{
    int longitud = 0;
    TListaPos aux;
    aux.pos = this->primero;
    while(!aux.EsVacia()){
        longitud++;
        aux = aux.Siguiente();
    }
    return longitud;
}

TListaPos TListaCom::Primera() const{
    TListaPos temp = TListaPos();
    temp.pos = this->primero;
    return temp;
}

TListaPos TListaCom::Ultima() const{
    TListaPos temp = TListaPos();
    temp.pos = this->ultimo;
    return temp;
}

TListaNodo TListaPos::ObtenerPos(){
    return *this->pos;
}

TComplejo TListaNodo::ObtenerE(){
    return this->e;
}

ostream & operator<<(ostream &s, const TListaCom &lista){
    s << "{"; 
    TListaPos temp = lista.Primera();
    while(!temp.EsVacia()){
        TComplejo e = temp.ObtenerPos().ObtenerE();
        s << e;
        temp = temp.Siguiente();
        if(!temp.EsVacia()){
            s << " ";
        }
    }
    s << "}";
    return s;

}