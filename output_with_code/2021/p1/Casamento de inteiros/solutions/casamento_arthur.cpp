#include <bits/stdc++.h>
#define ll long long
#define maxn 100100
#define pii pair<int,int>
#define pb push_back
#define debug 
using namespace std;

string A,B;

void print(vector<int> v){
	if(v.size() == 0) printf("-1");
	else for(int i=0;i<v.size();i++)
		printf("%c",v[i]);
}

int main(){

	cin >> A >> B;

	int n = A.length();
	int m = B.length();

	vector<int> ansA, ansB;

	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());

	while(n < m) A.pb('0'), n++;
	while(m < n) B.pb('0'), m++;

	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());

	for(int i=0;i<n;i++){

		if(A[i] <= B[i])
			ansB.pb(B[i]);
		if(B[i] <= A[i])
			ansA.pb(A[i]);
		
	}

	reverse(ansA.begin(), ansA.end());
	reverse(ansB.begin(), ansB.end());

	while(ansA.size() > 1 && ansA[ansA.size()-1] == '0') ansA.pop_back();
	while(ansB.size() > 1 && ansB[ansB.size()-1] == '0') ansB.pop_back();

	reverse(ansA.begin(), ansA.end());
	reverse(ansB.begin(), ansB.end());

	int swap = 0;

	if(ansB.size() < ansA.size()) swap = 1;

	if(ansB.size() == ansA.size()){
		for(int j=0;j<ansB.size();j++){
			if(ansA[j] != ansB[j]){
				if(ansB[j] < ansA[j])
					swap = 1;
				break;
			}
		}
	}

	if(swap){
		print(ansB);
		printf(" ");
		print(ansA);
		printf("\n");
	}
	else{
		print(ansA);
		printf(" ");
		print(ansB);
		printf("\n");
	}


}
