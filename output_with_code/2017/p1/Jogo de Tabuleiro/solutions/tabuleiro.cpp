#include <iostream>

#define MAX 101

using namespace std;

int t[MAX][MAX],N;

int main(){
  
  cin >> N;
  for ( int i = 1; i <= N; i++ )
    for ( int j = 1; j <= N; j++ )
      cin >> t[i][j];
  
  for ( int i = 2; i <= N; i++ )
    for ( int j = 2; j <= N; j++ )
      if ( t[i][j-1] + t[i-1][j-1] + t[i-1][j] >= 2 ){
	t[i][j] = 0;
      } else {
	t[i][j] = 1;
      } 

  cout << t[N][N] << endl;
  
  return 0;
}
