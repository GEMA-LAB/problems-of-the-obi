#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int mdc(int a, int b){
	if(b==0) return a;
	if(b>a) return mdc(b,a);
	return mdc(b,a%b);
}

int main(void){
	int C,D,Q;
	cin >> C >> D >> Q;
	int m = mdc(D,Q);
	D /= m;
	Q /= m;
	m = max(D,Q);

	if(m > C) printf("IMPOSSIVEL\n");
	else printf("%d %d\n",D,Q);

	return 0;

}
