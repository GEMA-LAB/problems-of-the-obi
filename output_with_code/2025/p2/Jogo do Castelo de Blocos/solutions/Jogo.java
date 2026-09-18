import java.util.*;
import java.util.LinkedList;
import java.util.Queue;
import java.lang.Math;


public class Jogo {
    static int apoio[] = new int[19];
    static int prox_estado[][] = new int[1<<19][19];
    static int dp[][] = new int[2][1<<19];
    static int quant_no_castelo[] = new int[1<<19];
    static Integer N, M;
    static ArrayList<ArrayList<Integer>> g;
    public static void pre_calcula_estados(int masc, int tira){
        if((masc & (1 << tira)) == 0)
            return;
        if(prox_estado[masc][tira] != -1)
            return;
        //salvando relacoes de apoio antes de tirar
        int temp[] = new int[19];
        for(int i = 0; i < N; i++) 
            temp[i] = apoio[i];

        //calculando mascara do prox estado
        Queue<Integer> q = new LinkedList<>();
        q.add(tira);
        int nova = masc ^ (1<<tira);
        while(!q.isEmpty()){
            int v = q.remove();
            for(int u : g.get(v)){
                if(((1<<u) & nova) != 0){
                    apoio[u]--;
                    if(apoio[u] == 0){
                        nova ^= (1<<u);
                        q.add(u);
                    }
                }
            }
            
        }
        prox_estado[masc][tira] = nova;

        //chamada recursiva
        for(int i = 0; i < N; i++)
            pre_calcula_estados(nova, i);

        //retomando relacoes de apoio antes de tirar
        for(int i = 0; i < N; i++) 
            apoio[i] = temp[i];
    }
    public static int calcula_dp(int masc, int maximizar){
        if(dp[maximizar][masc] != -1)
            return dp[maximizar][masc];

        int resposta;
        if(maximizar == 1)
            resposta = 0;
        else
            resposta = quant_no_castelo[masc];
        for(int i = 0; i < N; i++)
            if(((1<<i) & masc) != 0){
                int prox = prox_estado[masc][i];
                int desabados = quant_no_castelo[masc] - quant_no_castelo[prox] - 1;
                int atual = calcula_dp(prox, maximizar^1) + desabados;
                if(maximizar == 1)
                    resposta = Math.max(resposta, atual);
                else
                    resposta = Math.min(resposta, atual);
            }
        return dp[maximizar][masc] = resposta;
    }
        
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        N = input.nextInt();
        M = input.nextInt();
        
        g = new ArrayList<ArrayList<Integer>>();
        for(Integer i = 0; i <N; i++){
            g.add(new ArrayList<Integer>());
        }
        for(int i = 0; i < M; i++){
            int a = input.nextInt();
            int b = input.nextInt();
            a--;
            b--;
            g.get(a).add(b);
            apoio[b]++;
        }
        input.close();

        for(int masc = 0; masc < (1<<N); masc++){
            for(int i = 0; i < N; i++){
                prox_estado[masc][i] = -1;
                if(((1<<i) & masc) != 0)
                    quant_no_castelo[masc]++;
            }
            dp[0][masc] = dp[1][masc] = -1;
        }
        for(int i = 0; i < N; i++){
            int masc = (1<<N) - 1;
            pre_calcula_estados(masc, i);
        }
        System.out.println(calcula_dp((1<<N) - 1, 0));    

    }
}
