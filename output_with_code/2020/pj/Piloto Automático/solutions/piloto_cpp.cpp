// OBI-2020, piloto, Guilherme A. Pinto

#include <iostream>

using namespace std;

int main(){

  int A, B, C;

  cin >> A >> B >> C;

  int distAB = B-A;
  int distBC = C-B;

  if ( distAB < distBC ){
    cout << 1 << endl;
  } else {
    if ( distAB > distBC ){
      cout << -1 << endl;
    } else {
      cout << 0 << endl;
    }
  }

  return 0;
}