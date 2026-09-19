#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  string map;
  cin >> map;
  string s;
  cin >> s;
  for (int i = 0; i < s.size(); i++)
    if ('a' <= s[i] && s[i] <= 'z')
      s[i] = map[s[i]-'a'];
  cout << s << endl;
  return 0;
}
