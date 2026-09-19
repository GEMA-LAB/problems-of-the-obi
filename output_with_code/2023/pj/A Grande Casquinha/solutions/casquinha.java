import java.util.Scanner;
import java.util.Arrays;

public class casquinha {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int S = sc.nextInt();

        Boolean[] peguei = new Boolean[S+1];
        Arrays.fill(peguei, Boolean.FALSE);

        int X[] = new int[N];

        for (int i = 0; i < N; i++) {
            X[i] = sc.nextInt();
        }

        int resposta = 0;
        int l = 0;
        int atual = 0;

        for (int r = 0; r < N; r++) {
            while (peguei[X[r]]) {
                peguei[X[l]] = false;
                atual -= 1;
                l += 1;
            }

            peguei[X[r]] = true;
            atual += 1;
            resposta = resposta >= atual ? resposta : atual;
        }

        System.out.println(resposta);
    }
}
