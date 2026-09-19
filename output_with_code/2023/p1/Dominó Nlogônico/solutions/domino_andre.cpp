#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 300010;
int x[MAXN], h[MAXN], resp[MAXN];
vector<int> pilha;
int main() {
  int n;
  scanf("%d", &n);
  
  for(int i = 0; i < n; i++)
    scanf("%d", &x[i]);
  for(int i = 0; i < n; i++)
    scanf("%d", &h[i]);
  
  resp[n - 1] = 1;
  pilha.push_back(n - 1);
  for(int i = n - 2; i >= 0; i--) {
    resp[i] = 1;
    int idTopo = pilha.size() - 1;
    while((idTopo != -1) && ((x[i] + h[i]) >= x[pilha[idTopo]])) {
      resp[i] += resp[pilha[idTopo]];
      pilha.pop_back();
      idTopo--;
    }
    pilha.push_back(i);
  }
  
  for(int i = 0; i < n; i++)
    printf("%d%c", resp[i], i == n - 1 ? '\n' : ' ');
}