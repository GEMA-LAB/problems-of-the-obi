// calorias
// obi2020 - fase 3

#include <iostream>

using namespace std;

int main(void) {
  int e1, e2, e3, x;
  
  cin >> e1 >> e2 >> e3 >> x;
  if (e2 - e1 <= x)
    cout << e2 << endl;
  else
    cout << e3 << endl;
  return 0;
}
