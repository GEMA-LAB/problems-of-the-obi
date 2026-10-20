// OBI-2020, paciente, O(NC), linear na entrada, Guilherme A. Pinto

#include <iostream>
#include <vector>
using namespace std;

int N, C;
vector<bool> z;

int main(){

  cin >> N >> C;

  z = vector<bool>( N+1, true );

  for( int c = 0; c < C; c++ ){
    int P, I;
    cin >> P >> I;

    for( int i = 0; i < I; i++ ){
      int X;
      cin >> X;
      z[X] = false;
    }
  }


  for( int i = 1; i <= N; i++ )
    if ( z[i] )
      cout << i << endl;

  return 0;
}