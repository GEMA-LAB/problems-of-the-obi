#include <iostream>
using namespace std;

int main(){
  int C,A;
  
  cin >> C >> A;

  int quociente = A/(C-1);
  int resto = A%(C-1);

  int resposta = quociente;
  if ( resto > 0 ) resposta++;

  cout << resposta << endl;
  
  return 0;
}
