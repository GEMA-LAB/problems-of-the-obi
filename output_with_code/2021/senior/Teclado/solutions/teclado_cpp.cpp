// OBI2021 - Fase 3
// Teclado


#include <bits/stdc++.h>

using namespace std;

map<char, string> repr = {{'2', "abc"},
			  {'3', "def"},
			  {'4', "ghi"},
			  {'5', "jkl"},
			  {'6', "mno"},
			  {'7', "pqrs"},
			  {'8', "tuv"},
			  {'9', "wxyz"}};


int main(void){
  string num;
  int m;
  
  cin >> num;
  cin >> m;

  int resp = 0;
  for (int i=0; i<m; i++) {
    string palavra;
    cin >> palavra;

    // se têm comprimentos diferentes não é representação correta
    if (palavra.length() != num.length())
      continue;
    bool ok = true;
    // para cada letra da palavra, verifica se é representação correta
    for (int k=0; k<num.length(); k++) {
      if (repr[num[k]].find(palavra[k]) == string::npos) {
	ok = false;
	break;
      }
    }
    if (ok)
      resp++;
  }
  
  // imprime resposta
  cout << resp << endl;

  return 0;
}
