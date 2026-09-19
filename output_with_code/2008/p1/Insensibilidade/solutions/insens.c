#include <stdio.h>

int main() {
	long int N, i, tot;
	long int x1, x2, y1, y2, dx, dy;
	scanf(" %ld", &N);
	tot = 0;
	for (i = 0; i < N; i++) {
		scanf(" %ld %ld %ld %ld", &x1, &y1, &x2, &y2);
		dx = x2 - x1;
		dy = y2 - y1;
		tot += dx * dx + dy * dy;
	}
	printf("%ld\n", tot);
	return 0;
}
