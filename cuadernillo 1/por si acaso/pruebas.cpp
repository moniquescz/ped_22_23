#include <iostream>
#include "TVectorCom.h"
using namespace std;


int main(){
    TComplejo c1(1,0.5);
    TComplejo c2(3,0.5);
    TVectorCom v1(2);
    v1[1] = c1;
    v1[2] = c2;
    cout << v1;
    return 0;
}