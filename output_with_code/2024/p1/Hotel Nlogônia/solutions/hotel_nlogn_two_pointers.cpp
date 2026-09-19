/*
OBI 2024 - Fase 3
  Hotel Nlogônia
  Solução em O(N log N) com Two Pointers + Sets (ou "Sliding Window")
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
long long cur_tot; // soma da janela atual
int n, d;
long long w;

// vamos guardar todas as somas para intervalos de tamanho D na
// janela atual do two pointers, ordenados decrescente por soma,
// em um multiset para inserção/consulta do maior em O(log N)
multiset <long long> dsums;

// somas parciais:
// psum guarda somas de prefixo;
// dsum guarda somas de intervalos de tamanho D
long long p[MAXN], psum[MAXN], dsum[MAXN];

// usado no two pointers para decidir se o intervalo (l, r)
// satisfaz as condições do enunciado ou não
bool good(int l, int r) {
  if (r - l + 1 <= d) return true;
  long long largest_dsum = *dsums.rbegin();
  return cur_tot - largest_dsum <= (long long) w;
}

int main() {
  cin >> n >> d >> w;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    psum[i] = psum[i - 1] + p[i];
    if (i >= d) {
      dsum[i] = psum[i] - psum[i - d];
    }
  }

  // técnica de two pointers para encontrar o maior intervalo válido
  int resp = d;
  cur_tot = psum[d - 1];
  int l = 1;

  for (int r = d; r <= n; r++) {
    // adiciona r na janela do two pointers
    cur_tot += p[r];
    dsums.insert(dsum[r]);

    // enquanto o custo estiver muito alto, remove l da janela do two pointers
    while (!good(l, r)) {
      cur_tot -= p[l];
      dsums.erase(dsums.find(dsum[l + d - 1]));
      l++;
    }

    resp = max(resp, r - l + 1);
  }

  cout << resp << endl;
  return 0;
}
