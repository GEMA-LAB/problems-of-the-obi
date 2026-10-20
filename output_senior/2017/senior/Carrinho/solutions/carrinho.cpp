// Guilherme A. Pinto, OBI-2017, carrinho

#include <limits>
#include <iostream>
#include <iomanip>

#define MAX 1000

using namespace std;

double d[MAX+1],c[MAX+1];
double dp[MAX+1][MAX+1];

double s( int k, int i ){
  // base
  if ( k == 0 ) return 0.0;
  if ( i == -1 ) return numeric_limits<double>::max();
  // memoization
  if ( dp[k][i] != -1.0 ) return dp[k][i];

  return dp[k][i] = min(s(k,i-1),s(i,i-1)+(d[k]-d[i])*(d[k]-d[i])/c[i]);
}

int main(){
  int N,i,j;
  
  cin >> N;
  cin >> d[N];
  for ( i = 0; i < N; i++ )
    cin >> d[i] >> c[i];

  for ( i = 0; i <= N; i++ )
    for ( j = 0; j <= N; j++ )
      dp[i][j] = -1.0;
  
  cout << setprecision(3) << fixed;
  cout << s(N,N-1) << endl;
  return 0;
}
