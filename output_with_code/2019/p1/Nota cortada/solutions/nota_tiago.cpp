#include <bits/stdc++.h>
using namespace std;


int32_t main(){
	int b , t;
	int a = 70*160;
	cin>>b>>t;
	int c = 35*(b+t);
	a -= c;
	if(c > a){
		cout<<1<<endl;	
	}
	else if(a > c){
		cout<<2<<endl;
	}
	else cout<<0<<endl;
}