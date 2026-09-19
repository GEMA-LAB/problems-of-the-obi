#include <cstdio>
#include <cstring>

const int MAX = 100001;

int A[MAX];

int merge(int p, int q, int r) {
  int i, j, k, invs;
  int n1 = q - p + 1;
  int n2 = r - q;
  static int L[MAX], R[MAX];
  memcpy(L, A + p, sizeof(int)*n1);
  memcpy(R, A + (q + 1), sizeof(int)*n2);
  L[n1] = 0x7fffffff;
  R[n2] = 0x7fffffff;
  i = 0;
  j = 0;
  invs = 0;
  for (k = p; k <= r; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
      invs += j;
    }
    else {
      A[k] = R[j];
      j++;
    }
  }
  return invs;
}

int countInversions(int p, int r) {
  int q, li, ri, mi;
  if (p < r) {
    q = (p + r)/2;
    li = countInversions(p, q);
    ri = countInversions(q + 1, r);
    mi = merge(p, q, r);
    return li + ri + mi;
  }
  return 0;
}

int main() {
  
  for (int N; scanf("%d", &N) == 1 && (N);) {
    for (int n = 1; n <= N; n++) {
      scanf("%d", &A[n]);
    }
    printf("%d\n", countInversions(1, N));
  }
  
  return 0;
}
