#include <bits/stdc++.h>
using namespace std;

bool check_old(string plate) {
  if (plate.size() != 8) return false;
  for (int i = 0; i < 8; i++) {
    if (i < 3 && (plate[i] > 'Z' || plate[i] < 'A')) return false;
    if (i == 3 && plate[i] != '-') return false;
    if (i > 3 && (plate[i] > '9' || plate[i] < '0')) return false;
  }
  return true;
}

bool check_new(string plate) {
  if (plate.size() != 7) return false;
  for (int i = 0; i < 7; i++) {
    if ((i < 3 || i == 4) && (plate[i] > 'Z' || plate[i] < 'A')) return false;
    if ((i > 3 && i != 4) && (plate[i] > '9' || plate[i] < '0')) return false;
  }
  return true;
}

int main() {
  string plate;
  cin >> plate;
  if (check_old(plate)) cout << 1 << endl;
  else if (check_new(plate)) cout << 2 << endl;
  else cout << 0 << endl;
  return 0;
}
