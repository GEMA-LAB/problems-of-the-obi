import java.util.Scanner;
import java.util.Arrays;

public class aventura {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int dir[][] = {
            {0, 1},
            {1, 0},
            {0, -1},
            {-1, 0}
        }; 
        int x = 0, y = 0;
        int delta = 0;
        int t = sc.nextInt();       
        while(t > 0){
            t--;
            sc.nextLine();
            String comando = sc.nextLine();
            if(comando.equals("M")){
                int N = sc.nextInt();
                x += dir[delta][0] * N;
                y += dir[delta][1] * N;
            }
            if(comando.equals("G")){
                int P = sc.nextInt();
                P /= 90;
                delta = (delta + P) % 4;
            }
        }

        System.out.printf("%d %d\n",x ,y);
    }
}