// OBI 2023 - Fase 2
// Distintos - Solução O(N log N) com busca binária na resposta
//             e janela deslizante
// Mateus Bezrutchka
//
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = (int)1e5 + 10;
int v[MAXN];
int n;

int num_active; // numero de valores distintos que existem na janela atual
int cur_cnt[MAXN]; // numero de ocorrencias do valor na janela atual

void init_cnt() {
  for (int i = 0; i < MAXN; i++) {
    cur_cnt[i] = 0;
  }
  num_active = 0;
}

void increase_cnt(int x) {
  cur_cnt[x]++;
  if (cur_cnt[x] == 1) num_active++;
}

void decrease_cnt(int x) {
  cur_cnt[x]--;
  if (cur_cnt[x] == 0) num_active--;
}

// checa se existe um intervalo de tamanho sz com todos os elementos distintos
bool interval_exists(int sz) {
  init_cnt();
  for (int right = 1; right <= n; right++) {
    int left = right - sz;
    if (left > 0) decrease_cnt(v[left]);
    increase_cnt(v[right]);
    if (num_active == sz) return true;
  }
  return false;
}

int bin_search() {
  // invariante: left sempre eh uma resposta possivel
  int left = 1, right = n;
  while (left < right) {
    int mid = (left + right + 1) / 2;
    if (interval_exists(mid)) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  return left;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }
  printf("%d\n", bin_search());
  return 0;
}
