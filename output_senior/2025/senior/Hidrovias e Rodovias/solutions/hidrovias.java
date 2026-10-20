import java.util.*;

public class hidrovias {
    static final int MAXN = 100000 + 10;
    static int[] dsu_parent = new int[MAXN];
    static int[] dsu_depth = new int[MAXN];

    static void dsu_init(int n) {
        for (int i = 1; i <= n; i++) {
            dsu_parent[i] = i;
            dsu_depth[i] = 0;
        }
    }

    static int dsu_find(int v) {
        if (v == dsu_parent[v]) return v;
        return dsu_parent[v] = dsu_find(dsu_parent[v]);
    }

    static boolean dsu_union(int u, int v) {
        u = dsu_find(u);
        v = dsu_find(v);
        if (u == v) {
            return false;
        }
        if (dsu_depth[u] < dsu_depth[v]) {
            int temp = u;
            u = v;
            v = temp;
        }
        dsu_parent[v] = u;
        if (dsu_depth[u] == dsu_depth[v]) {
            dsu_depth[u]++;
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();
        int k = sc.nextInt();

        List<int[]> edges = new ArrayList<>();
        while (m-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int t = sc.nextInt();
            edges.add(new int[]{t, a, b});
        }

        dsu_init(n);

        // ordenar pelas arestas pelo "t"
        edges.sort(Comparator.comparingInt(e -> e[0]));

        int min_removals = 0;
        boolean hydro_cycle = false;

        for (int[] edge : edges) {
            int t = edge[0];
            int a = edge[1];
            int b = edge[2];

            boolean ret = dsu_union(a, b);
            if (!ret) {
                if (t == 1) hydro_cycle = true;
                else min_removals++;
            }
        }

        if (hydro_cycle) {
            System.out.println("N");
        } else if (min_removals > k) {
            System.out.println("N");
        } else {
            System.out.println("S");
        }

        sc.close();
    }
}
