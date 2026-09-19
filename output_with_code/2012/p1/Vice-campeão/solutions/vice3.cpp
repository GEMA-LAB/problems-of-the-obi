#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(){
	int A, B, C;
	scanf("%d%d%d", &A, &B, &C);
	B = min(max(A, B), min(max(A, C), max(B, C)));
	printf("%d\n", B);
	return 0;
}

