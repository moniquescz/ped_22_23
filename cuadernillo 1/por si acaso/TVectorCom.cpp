#include "TVectorCom.h"

TVectorCom::TVectorCom(){
    this->c = NULL;
    this->tamano=0;
}

TVectorCom::TVectorCom (int t){
    if (t<=0){
        this->c = NULL;
        this->tamano=0;
    }else{
        this->c = new TComplejo[t];
        this->tamano=t;
    }
}

TVectorCom::TVectorCom (const TVectorCom &obj){
    //MOdificar y copiar elemento a elemento
    this->c=obj.c;
    this->tamano=obj.tamano;
}

TVectorCom::~TVectorCom (){
    delete[] this->c;
    this->c = NULL;
    this->tamano = 0;
}

TVectorCom& TVectorCom::operator=(const TVectorCom &obj){
    if (this!=&obj){
        (*this).~TVectorCom();
        this->c=obj.c;
        this->tamano=obj.tamano;
    }
    return *this;
}

bool TVectorCom::operator==(const TVectorCom &obj){
    bool temp = false;
    if (this->c==obj.c && this->tamano==obj.tamano){
        temp = true;
    }
    return temp;
}

bool TVectorCom::operator!=(const TVectorCom &obj){
    bool temp = true;
    if (this->c==obj.c && this->tamano==obj.tamano){
        temp = false;
    }
    return temp;
}

TComplejo& TVectorCom::operator[](int i){
    //TComplejo temp;
    if(i>=1 && i<=this->tamano){
        return this->c[i-1];
    }else{
        return this->error;
    }
    //return temp;
}

TComplejo TVectorCom::operator[](int i) const{
    //TComplejo temp;
    if(i>=1 && i<=this->tamano){
        return this->c[i-1];
    }else{
        return this->error;
    }
    //return temp;
}

int TVectorCom::Tamano(){
    int temp = this->tamano;
    return temp;
}

int TVectorCom::Ocupadas(){
    int temp = 0;
    TComplejo aux = TComplejo();
    for (int i=0;i<this->tamano;i++){
        if (this->c[i] != aux){
            temp++;
        }
    }
    return temp;
}

bool TVectorCom::ExisteCom(const TComplejo &obj){
    bool exists = false;
    for (int i=0;i<this->tamano && !exists;i++){
        if (this->c[i] == obj){
            exists = true;
        }
    }
    return exists;
}

void TVectorCom::MostrarComplejos(double d){
    cout << "[";
    for (int i=0;i<this->tamano;i++){
        if (this->c[i].Re()>=d){
            cout << this->c[i];
            if (i!=this->tamano-1){
                cout << ", ";
            }
        }
    }
    cout << "]" << endl;
}

bool TVectorCom::Redimensionar(int dim){
    bool temp = true;
    TComplejo *aux;
    if (dim<=0){
        temp = false;
    }else if (dim == this->tamano){
        temp = false;
    }else if (dim>0 && dim>this->tamano){
        aux = new TComplejo[dim];
        for (int i=0;i<this->tamano;i++){
            aux[i] = this->c[i];
        }
        delete[] this->c;
        this->c = aux;
        this->tamano = dim;
    }else if(dim>0 && dim<this->tamano){
        aux = new TComplejo[dim];
        for (int i=0;i<dim;i++){
            aux[i] = this->c[i];
        }
        delete[] this->c;
        this->c = aux;
        this->tamano = dim;
    }
    return temp;
}


ostream & operator<<(ostream &s, TVectorCom &obj){  
    s << "[";
    for (int i=0;i<obj.tamano;i++){
        s << "(" << i+1 << ") ";
        s << obj.c[i];
        if (i!=obj.tamano-1){
            cout << ", ";
        }
    }
    s << "]";
    return s;
}