// Guilherme A. Pinto, OBI 2017, zip

#include <iostream>
using namespace std;

int pontuacao( int a, int b ){
  int p = a + b;
  if ( a == b ) p *= 2;
  if ( abs(a-b) == 1 ) p *= 3;
  return p;
}

int main(){
  int l1,l2,c1,c2;
  
  cin >> l1 >> l2 >> c1 >> c2;
  int pLia = pontuacao( l1, l2 );
  int pCarolina = pontuacao( c1, c2 );

  if ( pLia == pCarolina )
    cout << "empate" << endl;
  else if ( pLia > pCarolina )
    cout << "Lia" << endl;
  else
    cout << "Carolina" << endl;
  
  return 0;
}
