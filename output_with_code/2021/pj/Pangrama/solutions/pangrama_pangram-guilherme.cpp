// Guilherme A. Pinto, pangram

#include <bits/stdc++.h>
using namespace std;

int main(){
  set<char> s;
  string line;

  getline( cin, line );
  for ( char c : line ) s.insert( c );
  s.erase( ' ' );
  s.erase( ':' );
  s.erase( ',' );
  cout << (s.size() == 23 ? 'S' : 'N') << endl;  
  return 0;  
}
