#include<bits/stdc++.h>

using namespace std;

int main(){
	int n, s;
	cin >> n >> s;
	int sum = 0, res = 0;
	for(int i = 0;i < n;i++){
		int x;
		cin >> x;
		if(sum + x > s){
			sum = x;
			res++;
		}
		else{
			sum += x;
		}
	}
	cout << res+1 << '\n';
	return 0;
}