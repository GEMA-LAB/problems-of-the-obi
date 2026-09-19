import java.util.Scanner;

public class Doces_java {    
    public static void main(String[] args) {

        Long N, preco_total = 0l;

        Scanner sc = new Scanner(System.in);
        N = sc.nextLong();
        sc.close();

        for(Long d = 1l; d <= N; d++){
            if(N % d == 0l){
                Long c = N / d;
                Long caixa_simples = (10l + 3l * d);
                Long caixa_enfeitada = (2l + c) * caixa_simples;
                Long pedido = caixa_enfeitada * c;
                preco_total += pedido;
            }
        }

        System.out.println(preco_total);
    }
}