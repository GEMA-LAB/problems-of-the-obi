#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int guess[6], correct[6];

  for (int i = 0; i < 6; i++) cin >> guess[i];
  for (int j = 0; j < 6; j++) cin >> correct[j];

  int ret = 0;

  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 6; j++)
      if (guess[i] == correct[j])
	ret++;

  const char *azar = "azar";
  const char *names[] = {azar, azar, azar, "terno", "quadra", "quina", "sena"};

  cout << names[ret] << endl;

  return 0;
}
