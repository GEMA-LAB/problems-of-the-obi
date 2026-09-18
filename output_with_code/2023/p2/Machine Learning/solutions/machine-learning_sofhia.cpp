#include <bits/stdc++.h>
using namespace std;

int main(){
	
	int N, X;
	cin >> N;

	map < string, string > dicionario;
	map < string, int > cont;

	for(int i = 0 ; i < N ; i++){
		string S;
		int k;
		cin >> S >> k;

		cont[S] = 0;
		for(int j = 0 ; j < k ; j++){
			string si;
			cin >> si;
			dicionario[si] = S;
		}
	}

	cin >> X;
	int maior_valor = 0;
	string topico_do_artigo = "";

	for(int i = 0 ; i < X ; i++){
		string si;
		cin >> si;

		if(dicionario.count(si) == 0) continue;

		cont[dicionario[si]]++;
	
		if(cont[dicionario[si]] > maior_valor || (cont[dicionario[si]] == maior_valor && topico_do_artigo > dicionario[si])){
			maior_valor = cont[dicionario[si]];
			topico_do_artigo = dicionario[si];
		}
	}

	cout << topico_do_artigo << "\n";

}