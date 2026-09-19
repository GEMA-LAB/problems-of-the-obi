#include "bits/stdc++.h"
using namespace std;

signed main(){
	int a, b, r, g;
	cin>>a>>b>>r>>g;

	bool ok = 1;

	if (2 * r > a)
		ok = 0;

	if (2 * r > b)	
		ok = 0;

	if ((360 % g) != 0)
		ok = 0;

	if (ok)
		cout<<"S"<<endl;
	else
		cout<<"N"<<endl;			
}