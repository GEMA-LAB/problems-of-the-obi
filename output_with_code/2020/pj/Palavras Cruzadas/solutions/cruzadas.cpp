// OBI2020
// cruzadas

#include <iostream>
#include <cstring>
using namespace std;

int main(void) {
  int indice_h = -1, indice_v = -1;
  string horizontal;
  string vertical;
  bool ok = true;

  getline(cin, horizontal);
  getline(cin, vertical);
  for (int i=horizontal.length()-1; i>=0; i--) {
    for (int j=vertical.length()-1; j>=0; j--) {
      if (horizontal[i] == vertical[j]) {
	indice_h = i+1;
	indice_v = j+1;
	ok = false;
	break;
      }
    }
    if (not ok)
      break;
  }
  cout << indice_h << " " << indice_v << endl;

  return 0;
}
