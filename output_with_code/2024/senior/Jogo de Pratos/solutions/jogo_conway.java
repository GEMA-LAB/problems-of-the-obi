import java.util.*;

public class conway
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
    int n = in.nextInt(), q = in.nextInt();
    int[][][] conway = new int[n][n][q + 1];
    for(int i = 0; i < n; i++) {
      String s = in.next();
      for(int j = 0; j < n; j++)
        if(s.substring(j, j + 1).equals("0")) conway[i][j][0] = 0;
        else conway[i][j][0] = 1;
    }
    for(int qq = 1; qq <= q; qq++) {
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          int viz = 0;
          for(int dx = -1; dx <= 1; dx++) {
            for(int dy = -1; dy <= 1; dy++) {
              if(dx == 0 && dy == 0) continue;
              if(i + dx < 0 || i + dx >= n) continue;
              if(j + dy < 0 || j + dy >= n) continue;
              
              viz += conway[i + dx][j + dy][qq - 1];
            }
          }
          
          //Se uma célula morta possuir exatamente três vizinhas vivas ela vira uma célula viva.
          if((conway[i][j][qq - 1] == 0) && (viz == 3))  conway[i][j][qq] = 1;
          //Se uma célula morta possuir uma quantidade de vizinhas diferente de três, ela continua morta
          if((conway[i][j][qq - 1] == 0) && (viz != 3))  conway[i][j][qq] = 0;
          //Se uma célula viva possuir duas ou três vizinhas vivas ela continua viva.
          if((conway[i][j][qq - 1] == 1) && ((viz == 2) || (viz == 3))) conway[i][j][qq] = 1;
          //Se uma célula viva possuir menos que duas vizinhas vivas ela morre.
          if((conway[i][j][qq - 1] == 1) && (viz < 2))  conway[i][j][qq] = 0;
          // Se uma célula viva possuir mais que três vizinhas vivas ela morre.
          if((conway[i][j][qq - 1] == 1) && (viz > 3))  conway[i][j][qq] = 0;
        }
      }
    }
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        System.out.print(conway[i][j][q]);
      }
      System.out.println();
    }
	}
}
