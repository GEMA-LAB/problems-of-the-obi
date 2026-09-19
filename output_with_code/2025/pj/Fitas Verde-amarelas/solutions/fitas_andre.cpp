#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1010;
int n, m, qtdcomp;
char mapa[MAXN][MAXN];
int marc[MAXN][MAXN];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
bool isInside(int i, int j) {
    return (1 <= i) && (i <= n) && (1 <= j) && (j <= m);
}
vector<pair<int, int>> cel_linhas;
vector<pair<int, int>> cel_colunas;
void dfs(int i, int j) {
    marc[i][j] = qtdcomp;
    cel_linhas.push_back({i, j});
    cel_colunas.push_back({j, i});
    for(int k = 0; k < 4; k++) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if(!isInside(ni, nj)) continue;
        if(mapa[ni][nj] != '#') continue;
        if(marc[ni][nj] != 0) continue;
        dfs(ni, nj);
    }
}
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            scanf(" %c", &mapa[i][j]);
    qtdcomp = 0;
    int resp = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(mapa[i][j] == '#' && marc[i][j] == 0) {
                qtdcomp++;
                cel_linhas.clear();
                cel_colunas.clear();
                dfs(i, j);
                
                sort(cel_linhas.begin(), cel_linhas.end());
                int fitas_verde = 1;
                for(int k = 1; k < cel_linhas.size(); k++)
                    if(!((cel_linhas[k].first == cel_linhas[k - 1].first) && (cel_linhas[k].second == cel_linhas[k - 1].second + 1)))
                        fitas_verde++;
                
                sort(cel_colunas.begin(), cel_colunas.end());
                int fitas_amarela = 1;
                for(int k = 1; k < cel_colunas.size(); k++)
                    if(!((cel_colunas[k].first == cel_colunas[k - 1].first) && (cel_colunas[k].second == cel_colunas[k - 1].second + 1)))
                        fitas_amarela++;
                
                resp += min(fitas_verde, fitas_amarela);
            }
    printf("%d\n", resp);
}