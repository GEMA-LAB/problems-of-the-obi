#include <bits/stdc++.h>
using namespace std;

int main() {
  int d;
  cin >> d;

  int resp;
  if (d <= 200) resp = d;
  else if (d <= 400) resp = 400 - d;
  else if (d <= 600) resp = d - 400;
  else if (d <= 800) resp = 800 - d;
  else if (d <= 1000) resp = d - 800;
  else if (d <= 1200) resp = 1200 - d;
  else if (d <= 1400) resp = d - 1200;
  else if (d <= 1600) resp = 1600 - d;
  else if (d <= 1800) resp = d - 1600;
  else resp = 2000 - d;

  cout << resp << endl;
  return 0;
}
