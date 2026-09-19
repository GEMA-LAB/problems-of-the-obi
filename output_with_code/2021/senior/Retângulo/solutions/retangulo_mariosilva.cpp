// OBI2021
// retangulos

#include <bits/stdc++.h>

using namespace std;

const int N = 100009;

int n, x[N], whole_circle;

bool process() {
	if (whole_circle%2 != 0) return false;
	int half_circle = whole_circle/2;

	//amount of pairs of antipodal points
	int antipodal_pairs = 0;

	int arc_dist = 0;
	for (int i = 0, j = 0; i < n; i++) {
		while (j < n-1 && arc_dist < half_circle) {
			arc_dist += x[j];
			j++;
		}

		if (arc_dist == half_circle) {
			antipodal_pairs++;
			if (antipodal_pairs == 2) return true;
		}

		arc_dist -= x[i];
	}

	return false;
}

int main() {
	scanf("%d", &n);
	whole_circle = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d", x+i);
		whole_circle += x[i];
	}

	if (process()) printf("S\n");
	else printf("N\n");

	return 0;
}




































