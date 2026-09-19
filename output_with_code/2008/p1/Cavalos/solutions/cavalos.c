#include <stdio.h>

int main() {
	int M, N, t, ans;
	scanf(" %d %d", &M, &N);
	if (M > N) {
		t = M;
		M = N;
		N = t;
	}
	if (M >= 3) {
		ans = (M * N + 1) / 2;
	} else if (M == 2) {
		switch (N % 4) {
			case 0:
				ans = N;
				break;
			case 2:
				ans = N + 2;
				break;
			case 1:
			case 3:
				ans = N + 1;
				break;
		}
	} else {
		ans = N;
	}
	printf("%d\n", ans);
	return 0;
}
