import java.util.Scanner;
import java.util.Queue;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;

public class Castelo {    
    public static void main(String[] args) {

        Integer N, M, K;

        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        K = sc.nextInt();

        int[] R = new int[N];
        int[] apoio = new int[N];
        boolean [] quebrado = new boolean[N];
        boolean[] retirado = new boolean[N];
        boolean[] tentar_retirar = new boolean[N];
        ArrayList<ArrayList<Integer>> g = new ArrayList<ArrayList<Integer>>();
        for(Integer i = 0; i <N; i++){
            g.add(new ArrayList<Integer>());
        }
        for(Integer i = 0; i < M; i++){
            Integer a, b;
            a = sc.nextInt();
            b = sc.nextInt();
            a--; b--;
            g.get(a).add(b);
            apoio[b]++;
        }
        for(Integer i = 0; i < K; i++){
            R[i] = sc.nextInt();
            R[i]--;
            tentar_retirar[R[i]] = true;
        }
        sc.close();
        for(Integer r = 0; r < K; r++){
            Integer i = R[r];
            Queue<Integer> q = new LinkedList<>();
            if(tentar_retirar[i] && ! quebrado[i]){
                q.add(i);
                retirado[i] = true;
                while(! q.isEmpty()){
                    int v = q.remove();
                    for(int u : g.get(v)){
                        apoio[u]--;
                        if(apoio[u] == 0 && ! retirado[u]){
                            quebrado[u] = true;
                            q.add(u);
                        }
                    }
                }
            }
        }

        int resposta = 0;
        for(Integer i = 0; i < N; i++)
            if(quebrado[i])
                resposta++;

        System.out.println(resposta);
    }
}