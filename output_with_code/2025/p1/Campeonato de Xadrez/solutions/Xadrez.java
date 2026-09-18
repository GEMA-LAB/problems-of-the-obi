import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;

public class Xadrez {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int M = scanner.nextInt();
        int K = scanner.nextInt();
        Integer P[] = new Integer[N];
        for(Integer i = 0; i < N; i++){
            P[i] = scanner.nextInt();
        }
        scanner.close();
        int left = 0, right = 100001;
        while(left + 1 < right){
            int mid = (left + right) / 2;
            int groups = 0;
            int cur = 0;
            for(Integer i =0; i < N; i++){
                if(P[i] < mid){
                    cur++;
                }
                if(cur == M){
                    groups++;
                    cur = 0;
                }
            }
            if(groups >= K)
                right = mid;
            else
                left = mid;
        }
        if(right == 100001)
            right = -1;
        System.out.println(right);
    }
}