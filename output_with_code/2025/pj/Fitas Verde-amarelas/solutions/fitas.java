import java.util.*;

public class fitas {
    static final int MAXN = 1001;
    static final int MAXC = MAXN * MAXN;
    static int[] dl = {-1, 0, 1, 0};
    static int[] dc = {0, 1, 0, -1};

    static int n, m;
    static char[][] grid = new char[MAXN][MAXN];
    static int[][] comp = new int[MAXN][MAXN];
    static int comp_atual = 0;
    static int[] fitas_hor = new int[MAXC];
    static int[] fitas_ver = new int[MAXC];

    // busca em largura
    static void bfs(int orig_l, int orig_c) {
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{orig_l, orig_c});
        comp[orig_l][orig_c] = comp_atual;

        while (!q.isEmpty()) {
            int[] p = q.poll();
            int l = p[0], c = p[1];

            for (int i = 0; i < 4; i++) {
                int nl = l + dl[i];
                int nc = c + dc[i];
                if (nl <= 0 || nl > n || nc <= 0 || nc > m) continue;
                if (grid[nl][nc] == '#' && comp[nl][nc] == 0) {
                    comp[nl][nc] = comp_atual;
                    q.add(new int[]{nl, nc});
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        sc.nextLine();

        for (int l = 1; l <= n; l++) {
            String linha = sc.nextLine();
            for (int c = 1; c <= m; c++) {
                grid[l][c] = linha.charAt(c - 1);
            }
        }

        // encontra componentes conexas
        for (int l = 1; l <= n; l++) {
            for (int c = 1; c <= m; c++) {
                if (grid[l][c] == '#' && comp[l][c] == 0) {
                    comp_atual++;
                    bfs(l, c);
                }
            }
        }

        // testa colocar fitas horizontais em cada componente
        for (int l = 1; l <= n; l++) {
            for (int c = 1; c <= m; c++) {
                if (grid[l][c] != '#') continue;
                if (c == 1 || grid[l][c - 1] != '#') {
                    fitas_hor[comp[l][c]]++;
                }
            }
        }

        // testa colocar fitas verticais em cada componente
        for (int c = 1; c <= m; c++) {
            for (int l = 1; l <= n; l++) {
                if (grid[l][c] != '#') continue;
                if (l == 1 || grid[l - 1][c] != '#') {
                    fitas_ver[comp[l][c]]++;
                }
            }
        }

        // pega a melhor opcao pra cada componente
        int resp = 0;
        for (int i = 1; i <= comp_atual; i++) {
            resp += Math.min(fitas_hor[i], fitas_ver[i]);
        }

        System.out.println(resp);
        sc.close();
    }
}
