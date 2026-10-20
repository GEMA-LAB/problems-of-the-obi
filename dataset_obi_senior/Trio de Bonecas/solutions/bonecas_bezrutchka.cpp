/**
 * OBI 2023 - Fase 3
 * Trio de Bonecas - Solução O(NK) com Programação Dinâmica
 * Mateus Bezrutchka
 *
 * Ordenamos as bonecas em ordem crescente.
 * Seja dp[i][j] a resposta para as bonecas de j a N formando j trios.
 *
 * Vamos analisar a transição da DP:
 * -> Se a boneca i não pertence a um dos trios, temos
 *      dp[i][j] = dp[i + 1][j].
 *
 * -> Se a boneca i pertence a um trio, então ela é a menor desse trio
 *    (ainda não estamos incluindo as bonecas menores que ela).
 *    Podemos provar, por um argumento de troca, que a opção gulosa de
 *    usar a boneca i + 1 no mesmo trio que a boneca i é ótima:
 *    Se uma solução contém os trios (i, a, b) e (i + 1, c, d),
 *    podemos trocá-los pelos trios (i, i + 1, b) e (a, c, d) sem piorar
 *    a resposta, pois necessariamente c > a > i + 1 > i.
 *    Logo, usando a boneca i + 1,
 *      dp[i][j] = (t[i + 1] - t[i])^2 + dp[i + 2][j - 1].
 *
 * -> Observe que, na transição acima, só escolhemos as duas menores
 *    bonecas de cada trio. Para a maior, podemos escolher qualquer
 *    boneca maior ou igual às duas, mas precisamos garantir que temos
 *    bonecas o suficiente. Isso é simples -- temos bonecas suficientes
 *    se e somente se
 *      3j <= N + 1 - i.
 *    Então basta setar para INF todos os estados que não satisfazem
 *    essa desigualdade, e tirar o mínimo dos dois casos acima.
 *
 * A resposta final é dp[1][K].
 **/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10100;
const int MAXK =  3100;
const long long INF = (long long)1e18 + 10;

long long dp[MAXN][MAXK];
bool seen[MAXN][MAXK];
int N, K;
int t[MAXN];

// usei (n, k) ao invés de (i, j)
long long calc_dp(int n, int k) {
  if (seen[n][k]) return dp[n][k];
  seen[n][k] = true;

  if (n == N + 1) {
    if (k == 0) return dp[n][k] = 0;
    else return dp[n][k] = INF;
  }

  if (3 * k > N - n + 1) {
    return dp[n][k] = INF;
  }

  // nao usando atual
  dp[n][k] = calc_dp(n + 1, k);
  if (k == 0) return dp[n][k];

  // usando atual como menor
  dp[n][k] = min(
    dp[n][k],
    (t[n + 1] - t[n]) * (t[n + 1] - t[n]) + calc_dp(n + 2, k - 1)
  );

  return dp[n][k];
}

int main() {
  cin >> N >> K;
  for (int i = 1; i <= N; i++) {
    cin >> t[i];
  }
  sort(t + 1, t + N + 1);

  cout << calc_dp(1, K) << endl;
  return 0;
}
