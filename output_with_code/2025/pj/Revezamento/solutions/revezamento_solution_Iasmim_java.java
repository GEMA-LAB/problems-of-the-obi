import java.util.Scanner;
import java.util.Arrays;

public class solution_Iasmim_java {

    private static final long oo = 1_000_000_001L;

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        long ans = 4 * oo;

        long[][][] best = new long[2][4][2];
        long[][] v = new long[n + 1][4];
        long[][] pos = new long[2][2];

        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 4; j++){
                Arrays.fill(best[i][j], n);
            }
        }
        Arrays.fill(v[n], oo);

        for (int i = 0; i < n; i++){
            int t = sc.nextInt();
            for (int j = 0; j < 4; j++){
                v[i][j] = sc.nextLong();

                long p1 = best[t][j][0];
                long p2 = best[t][j][1];

                if (v[i][j] <= v[(int)p1][j]){
                    best[t][j][1] = best[t][j][0];
                    best[t][j][0] = i;
                } 
                else if (v[i][j] <= v[(int)p2][j]){
                    best[t][j][1] = i;
                }
            }
        }
        
        sc.close();

        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 4; j++){
                if (best[i][j][1] == n){
                    System.out.println("-1");
                    return;
                }
            }
        }

        for (int aa = 0; aa < 4; aa++){
            for (int bb = 0; bb < 4; bb++){
                if (bb == aa) continue;
                for (int cc = 0; cc < 4; cc++){
                    if (cc == aa || cc == bb) continue;
                    
                    int dd = 6 - aa - bb - cc;

                    int[] p = {aa, bb, cc, dd};
                    long atual = 0;
                    
                    for (int i = 0; i < 4; i++){
                        pos[p[i] & 1][(p[i] / 2) & 1] = i;
                    }

                    for (int i = 0; i < 2; i++){
                        long[] p1 = {best[i][(int)pos[i][0]][0], best[i][(int)pos[i][0]][1]};
                        long[] p2 = {best[i][(int)pos[i][1]][0], best[i][(int)pos[i][1]][1]};

                        if (p1[0] != p2[0]){
                            atual += v[(int)p1[0]][(int)pos[i][0]];
                            atual += v[(int)p2[0]][(int)pos[i][1]];
                        } 
                        else{
                            long a1 = v[(int)p1[0]][(int)pos[i][0]] + v[(int)p2[1]][(int)pos[i][1]];
                            long a2 = v[(int)p1[1]][(int)pos[i][0]] + v[(int)p2[0]][(int)pos[i][1]];
                            atual += Math.min(a1, a2);
                        }
                    }
                    ans = Math.min(ans, atual);
                }
            }
        }

        System.out.println(ans);
    }
}