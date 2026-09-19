import java.util.*;

public class estrada {
    static int query[][];
    static int last[], p[];
    static long ans[], sum[], sz[];
    static int find(int u){
        while(p[u] != u){
            if(p[p[u]] != p[u])
                p[u] = p[p[u]];
            u = p[u];
        }
        return u;
    }
    static void join(int u, int v, long w){
        u = find(u);
        v = find(v);
        ans[u] = ans[u] + ans[v] + sum[u] * sz[v] + sum[v] * sz[u] + w * sz[u] * sz[v];
        sum[u] = sum[u] + sum[v] + w * sz[v];
        sz[u] = sz[u] + sz[v];
        p[v] = u;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n, q;
        n = sc.nextInt();
        q = sc.nextInt();
        query = new int[q][];
        last = new int[n];
        for(int i=0;i<q;i++){
            int op;
            op = sc.nextInt();
            if(op == 1){
                int a, b, w;
                a = sc.nextInt();
                b = sc.nextInt();
                w = sc.nextInt();
                a--; b--;
                last[a] = i;
                last[b] = i;
                query[i] = new int[]{1, a, b, w};
            }  
            else{
                int v;
                v = sc.nextInt();
                v--;
                query[i] = new int[]{2, v, -1, -1};
            }
        }
        ans = new long[n];
        sum = new long[n];
        sz = new long[n];
        p = new int[n];
        for(int i=0;i<n;i++){
            p[i] = i; sz[i] = 1;
        }
        for(int i =0; i <q; i++){
            int op = query[i][0], a = query[i][1], b = query[i][2], w = query[i][3];
            
            if(op == 1){
                if(last[a] < last[b]){
                    int tmp = a;
                    a = b;
                    b = tmp;
                }
                join(a, b, w);
            }
            else if(op == 2){
                int v = find(a);
                System.out.println(ans[v]);
            }
        }
    }
}