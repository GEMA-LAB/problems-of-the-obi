// OBI 2023 - Fase 2
// Barcos - Solução com Union-Find e Small-To-Large
// Mateus Bezrutchka
//
// -- Ideia --
// Começando sem nenhuma aresta (barco), vamos adicionar as arestas em
// ordem decrescente de capacidade: se os vertices (ilhas) A e B se
// tornam conectados ao inserirmos uma aresta de capacidade CAP, então:
// - não existe caminho de A pra B com capacidade mínima maior que CAP
// - existe caminho de A pra B com capacidade mínima igual a CAP
// E portanto a resposta da consulta pro par (A, B) é CAP.
//
// Essa observação leva a uma solução offline (i.e. em que lemos todas as
// consultas antes de responder alguma): em cada vértice, guardamos os
// indices das consultas que incluem aquele vértice como inicio ou fim,
// e uma consulta é respondida quando a aresta adicionada torna os seus
// vertices conectados.
// 
// -- Union-Find (DSU) --
// Precisamos de uma estrutura que nos permita:
// - guardar, para cada componente, a lista de consultas ainda não
//   respondidas que contém vértices desse componente;
// - unir duas componentes, e checar quais consultas são respondidas
//   com a união atual.
// Isso pode ser feito com Union-Find (também conhecido como DSU)
// onde cada componente guarda, além dos campos usuais, um set de todas
// as consultas inclusas.
// 
// Qualquer implementação razoável dessa ideia é suficiente para os
// conjuntos de testes em que N é pequeno ou C = 1, mas pro caso geral
// precisamos garantir que as uniões de sets de consultas sejam eficientes.
// 
// -- Small to Large --
// Para conseguir unir os sets de consultas de maneira eficiente,
// usamos a técnica geral conhecida como "Small to Large":
// ao processar uma série de uniões de sets, sempre inserimos os
// elementos do menor set no maior set (e não o contrário).
// Dessa forma, cada vez que um elemento é movido de set, o tamanho do
// set em que ele se encontra no mínimo dobra, e portanto para C elementos
// cada elemento é movido no máximo log C vezes. No total, são O(C log C)
// inserções em set, dando uma complexidade de O(C log^2 C).
//
// Incluindo a ordenação das arestas e o Union-Find, a complexidade final é
// O(B log B + B * UF + C log^2 C)
// onde UF é a complexidade do Union-Find.
//
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = 100100;
int n, m, q;

struct edge {
  int a, b, c; // ilhas e capacidade
} edges[MAXN];
int parent[MAXN];
int depth[MAXN];

// indices de consultas ainda nao respondidas no componente
set <int> queries[MAXN];
int answer[MAXN];

bool comp_edges(edge x, edge y) {
  if (x.c != y.c) return x.c > y.c;
  if (x.b != y.b) return x.b > y.b;
  return x.a > y.a;
}

void dsu_init() {
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    depth[i] = 0;
  }
}

int dsu_find(int v) {
  if (v == parent[v]) return v;
  parent[v] = dsu_find(parent[v]);
  return parent[v];
}

void dsu_merge(int v, int w, int cur_cap) {
  v = dsu_find(v);
  w = dsu_find(w);
  if (v == w) return;

  // dsu merge
  if (depth[v] < depth[w]) swap(v, w);
  parent[w] = v;
  if (depth[v] == depth[w]) depth[v]++;

  // small-to-large sets merge
  bool swapped = false;
  if (queries[v].size() < queries[w].size()) {
    swap(v, w);
    swapped = true;
  }
  
  for (set<int>::iterator it = queries[w].begin();
      it != queries[w].end(); it++) {
    int q_idx = *it;
    if (queries[v].find(q_idx) != queries[v].end()) {
      // acabei de encontrar a resposta pra consulta com indice q_idx
      answer[q_idx] = cur_cap;
      queries[v].erase(q_idx);
    } else {
      // ainda nao encontrei o outro endpoint da consulta q_idx
      queries[v].insert(q_idx);
    }
  }
  queries[w].clear();

  if (swapped) {
    swap(queries[v], queries[w]);
  }
}

void solve() {
  // processa arestas ordenadas de maior pra menor capacidade
  sort(edges, edges + m, comp_edges);
  dsu_init();
  for (int i = 0; i < m; i++) {
    int v = edges[i].a, w = edges[i].b, cur_cap = edges[i].c;
    dsu_merge(v, w, cur_cap);
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
  }
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    queries[a].insert(i);
    queries[b].insert(i);
  }

  solve();

  for (int i = 0; i < q; i++) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
