import java.util.*;
class Tuple implements Comparable<Tuple> {
    Long x, y, z;
 
    public Tuple(Long x, Long y, Long z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }
 
 
    @Override public int compareTo(Tuple a)
    {
        // if the string are not equal
        if(this.x != a.x){
            if(this.x < a.x)
                return -1;
            return 1;
        }
        if(this.y != a.y){
            if(this.y < a.y)
                return -1;
            return 1;
        }
        if(this.z != a.z){
            if(this.z < a.z)
                return -1;
            return 1;
        }
        return 0;
    }
}
public class bombons {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n, m, t;
        n = sc.nextInt();
        m = sc.nextInt();
        t = sc.nextInt();
        int[][] p = new int[n][m];
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                p[i][j] = sc.nextInt();
            }
        }
        int x1, y1, x2, y2;
        x1 = sc.nextInt();
        y1 = sc.nextInt();
        x2 = sc.nextInt();
        y2 = sc.nextInt();
        x1 --; y1--; x2--; y2--;
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        int lo = 0, hi = 1_000_000_000;
        long inf = 1_000_000_000_000_000_000L;
        while(lo <= hi){
            int mid = (lo + hi) / 2;
            long [][] dist = new long[n][m];
            for(int i = 0; i < n; i++)
                for(int j =0; j <m; j++)
                    dist[i][j] = inf;
            PriorityQueue<Tuple> pq = new PriorityQueue<>();
            dist[x1][y1] = 0;
            pq.add(new Tuple((long)0, (long)x1, (long)y1));
            while(!pq.isEmpty()){
                Tuple cur = pq.remove();
                long d = cur.x;
                long x = cur.y;
                long y = cur.z;
                if(dist[(int)x][(int)y] < d || p[(int)x][(int)y] == -1) continue;
                for(int k=0;k<4;k++){
                    int nx = (int)x + dx[k];
                    int ny = (int)y + dy[k];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    Long nd = d + (long)(p[(int)x][(int)y]) * mid;
                    if(nd < dist[nx][ny]){
                        dist[nx][ny] = nd;
                        pq.add(new Tuple((long)nd, (long)nx, (long)ny));
                    }
                }
            }
            if(dist[x2][y2] > t) hi = mid - 1;
            else lo = mid + 1;
        }
        System.out.println(hi);



    }
}