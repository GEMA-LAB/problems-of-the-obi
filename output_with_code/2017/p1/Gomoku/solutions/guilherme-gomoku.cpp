// Guilherme A. Pinto, OBI-2017, gomuko

#include <iostream>

#define MAX 15

using namespace std;

int t[MAX][MAX];

bool verifica( int i, int j, int di, int dj ){
  int cor = t[i][j];
  for ( int k = 1; k < 5; k++ )
    if ( cor != t[i+(k*di)][j+(k*dj)] )
      return false;
  cout << cor << endl;
  return true;
}

int main()
{  
  for ( int i = 0; i < MAX; i++ )
    for ( int j = 0; j < MAX; j++ )
      cin >> t[i][j];

  for ( int i = 0; i < MAX; i++ )
    for ( int j = 0; j < MAX; j++ )
      if ( t[i][j] != 0 ){
	// horizontal
	if ( j <= MAX-5 )
	  if ( verifica( i, j, 0, 1 ) )
	    return 0;
	// vertical
	if ( i <= MAX-5 )
	  if ( verifica( i, j, 1, 0 ) )
	    return 0;
	// diagonal 1
	if ( i <= MAX-5 and j <= MAX-5 )
	  if ( verifica( i, j, 1, 1 ) )
	    return 0;
	// diagonal 2
	if ( i >= 4 and j <= MAX-5 )
	  if ( verifica( i, j, -1, 1 ) )
	    return 0;
      }

  cout << 0 << endl;
  return 0;
}
