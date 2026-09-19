#include <iostream>
#include <cassert>
using namespace std;

#define N_LOW 2
#define N_HIGH 100
#define C_LOW 1
#define C_HIGH 1000
#define S_LOW 1
#define S_HIGH N
#define NEXT 1
#define PREV -1

int main() {
	int N, C, S, X, i, cur, RES;
	
	cin >> N >> C >> S;
	assert(N_LOW <= N && N <= N_HIGH);
	assert(C_LOW <= C && C <= C_HIGH);
	assert(S_LOW <= S && S <= S_HIGH);
	
	RES = (S == 1 ? 1 : 0); cur = 1;
	for (i=0; i<C; i++) {
		cin >> X;
		assert(X == NEXT || X == PREV);
		
		cur += X;
		if (cur == 0) cur = N;
		if (cur == N+1) cur = 1;
		if (cur == S) RES++;
	}
	cout << RES << endl;

	return 0;
}
