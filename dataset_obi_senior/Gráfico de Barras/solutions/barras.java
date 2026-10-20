import java.util.*;

public class barras {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int[] x = new int[n];
    int h = 0;
    for(int j = 0; j < n; j++) {
        x[j] = in.nextInt();
        h = Math.max(h, x[j]);
    }
    int[][] mat = new int[h][n];
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < h; i++) {
            if(i < h - x[j]) mat[i][j] = 0;
            else mat[i][j] = 1;
        }
    }
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < n; j++)
            System.out.print(mat[i][j] + " ");
        System.out.println();
    }
  }
}

