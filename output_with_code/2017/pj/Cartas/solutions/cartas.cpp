// Guilherme A. Pinto, OBI-2017, cartas

#include <iostream>

using namespace std;

int main(){
  int A,B,C,falta;
  
  cin >> A >> B >> C;
  
  if ( A == B ) {
    falta = C;
  } else {
    if ( A == C ) {
      falta = B;
    } else {
      falta = A;
    }
  }
  
  cout << falta << endl;
  
  return 0;
}
