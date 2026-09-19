#include "stdio.h"

int main(){
	int a, b, r, g;
	scanf("%d %d %d %d", &a, &b, &r, &g);

	int ok = 1;

	if (2 * r > a)
		ok = 0;

	if (2 * r > b)	
		ok = 0;

	if ((360 % g) != 0)
		ok = 0;

	if (ok)
		printf("S\n");
	else
		printf("N\n");			
}