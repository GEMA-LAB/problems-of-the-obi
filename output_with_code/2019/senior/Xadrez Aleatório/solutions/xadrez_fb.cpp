// OBI-2019, xadrez, Guilherme A. Pinto

#include <iostream>

using namespace std;

int main(){
  int N, T;

  cin >> N >> T;

  if ( T == 0 ) cout << N << endl;

  if ( T == 1 ){
    int res = 0;
    for( int i = 1; i <= N-1; i++ )
      for( int j = i+1; j <= N; j++ )
        res++;

    cout << res*2 << endl;
  }

  if ( T == 2 ){
    int res = 0;
    for( int i = 1; i <= N-2; i++ )
      for( int j = i+1; j <= N-1; j++ )
        for( int k = j+1; k <= N; k++ )
          res++;

    cout << res << endl;
  }

  return 0;
}