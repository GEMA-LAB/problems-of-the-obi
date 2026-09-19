// OBI-2019, prestacao, Guilherme A. Pinto

#include <iostream>

using namespace std;

int main(){
  int V, P;

  cin >> V >> P;

  int quociente = V/P;
  int resto = V%P;

  for( int i = 0; i < resto; i++ )
    cout << quociente+1 << endl;

  for( int i = 0; i < P-resto; i++ )
    cout << quociente << endl;

  return 0;
}