// OBI-2019, pares, Guilherme A. Pinto

#include <iostream>

using namespace std;

#define MAXN 1000

int v[MAXN];

int main(){

  int N, I, F;

  cin >> N >> I >> F;

  for( int i = 0; i < N; i++ )
    cin >> v[i];

  int res = 0;

  for( int i = 0; i < N-1; i++ )
    for( int j = i+1; j < N; j++ ){
      int soma = v[i]+v[j];
      if ( I <= soma and soma <= F )
        res++;
    }

  cout << res << endl;

  return 0;
}