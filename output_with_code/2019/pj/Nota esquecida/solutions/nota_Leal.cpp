/*
	Matheus Leal V
	OBI 2019 - Fase 01 - Nota
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	int H = 70, W = 160, B, T;

	cin>>B>>T;

	int S1 = (B + T)*H, S2 = (W - B + W - T)*H;

	if(S1 > S2) cout<<"1\n";

	else if(S1 == S2) cout<<"0\n";

	else cout<<"2\n"; 
}