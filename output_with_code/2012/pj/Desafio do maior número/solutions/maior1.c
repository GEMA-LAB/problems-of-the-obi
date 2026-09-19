#include <stdio.h>

int main() {
	int N;
	int max = 1;
	while (scanf("%d", &N) != EOF && N) {
		if (N > max) max = N;
	}
	printf("%d\n", max);
	return 0;
}
