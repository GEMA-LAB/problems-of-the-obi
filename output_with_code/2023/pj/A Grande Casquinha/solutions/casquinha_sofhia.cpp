#include <bits/stdc++.h>
using namespace std;

int main(){

	int N, S;	
	
	cin >> N >> S;

	vector < int > mark(S+1, 0);
	
	int sorvetes[N+1];

	for(int i = 0 ; i < N ; i++){
		cin >> sorvetes[i];
	}

	int l = 0, r = 0;
	int qtd = 1, ans = 1;
	mark[sorvetes[0]] = 1;
	
	while(l <= r and l < N){
		r++;

		if(r == N) break;

		if(mark[sorvetes[r]]){
			r--;
			mark[sorvetes[l]] = 0;
			l++;
			qtd--;
			if(l > r){
				r++;
				qtd++;
				mark[sorvetes[r]] = 1;
			}
		}
		else{
			qtd++;
			ans = max(ans, qtd);
			mark[sorvetes[r]] = 1;
		}
	}

	cout << ans << "\n";
}