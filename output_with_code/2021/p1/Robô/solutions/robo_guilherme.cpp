#include <bits/stdc++.h>

using namespace std;

int main(){
  ios::sync_with_stdio(false);

  int N,C,S,pos,cmd,count;

  cin >> N >> C >> S;

  count = 0;
  pos = 1;

  if ( pos == S ) count++;

  while ( C-- > 0 ){
    cin >> cmd;

    pos += cmd;
    if ( pos < 1 ) pos = N;
    if ( pos > N ) pos = 1;
    if ( pos == S ) count++;
  }

  cout << count << endl;

  return 0;
}
