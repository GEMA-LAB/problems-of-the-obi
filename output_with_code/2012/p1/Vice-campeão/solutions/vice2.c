#include <stdio.h>

int main(){
	int A, B, C, tmp;
	scanf("%d%d%d", &A, &B, &C);
	if (A < B){
		tmp = A;
		A = B;
		B = tmp;
	}
	if (B < C){
		tmp = B;
		B = C;
		C = tmp;
	}
	if (A < B){
		tmp = A;
		A = B;
		B = tmp;
	}
	printf("%d\n", B);
	return 0;
}
