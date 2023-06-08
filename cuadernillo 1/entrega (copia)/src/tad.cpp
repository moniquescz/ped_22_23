/* Prueba:
     La sobrecarga de la operacion - para TListaCom
*/
#include <iostream>

using namespace std;

#include "tlistacom.h"

int
main(void)
{
cout << "Prueba 10" << endl;
  TComplejo a, b(1), c(2, 3), d(3,4);
  TListaCom l1,l2,l3;
  
  l1.InsCabeza(a);
  cout << "18" << l1 << endl;
  l1.InsertarD(b, l1.Ultima());
    cout  << "20" << l1 << endl;
  l1.InsertarD(c, l1.Primera());
    cout << "22" << l1 << endl;
  l2=l1;
    cout << "24" << l2 << endl;
  l3.InsCabeza(a); 
    cout << "26" << l3 << endl;
  
  l1=l1+l2+l3;
  cout<<"l1 = "<<l1<<endl;
  cout << "l1 deberia = {(0 0) (2 3) (1 0) (0 0) (2 3) (1 0) (0 0)}" << endl;

  l2=l1 - l3;
  cout<<"l2 = "<<l2<<endl;
  cout<<"l2 deberia = l2 = {(2 3) (1 0) (2 3) (1 0)}" <<endl;
  l2=l2 - l1;
  cout<<"l2 = "<<l2<<endl;
   
  return 0;
}
