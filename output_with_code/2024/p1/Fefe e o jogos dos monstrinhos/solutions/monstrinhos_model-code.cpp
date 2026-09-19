#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, F;
	cin >> N >> F;

	vector<int> M(N); for (int& m : M) cin >> m;
	vector<int> P(F); for (int& f : P) cin >> f;
	vector<int> B(F); for (int& f : B) cin >> f;

    for (int i = 0; i < F; ++i) {
        for (int j = i+1; j < F; ++j) {
            if (P[i] > P[j]) {
                swap(P[i], P[j]);
                swap(B[i], B[j]);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            if (M[i] > M[j]) {
                swap(M[i], M[j]);
            }
        }
    }
	
	for (int i = 0; i < F; ++i) {
		int first_alive = N;
		for (int j = 0; j < N; ++j) {
			if (M[j] > 0) {
				first_alive = j;
				break;
			}
		}
		for (int j = first_alive; j < N && B[i] > 0; ++j) {
			if (P[i] > M[j]) {
				M[j] = 0;
				B[i] -= 1;
			}
		}
	}
	
	int cnd = 0;
	for (int i = 0; i < N; ++i) {
		if (M[i] == 0) cnd += 1;
	}

    assert(0 <= cnd && cnd <= N);
    
	cout << cnd << '\n';
}
