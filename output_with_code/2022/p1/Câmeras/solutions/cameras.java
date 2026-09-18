// OBI2022 - Fase 2
// Tarefa Cameras
// Yan Silva

import java.util.Scanner;

public class cameras {

    public static int[] dx = {0, 0, 1, -1};
    public static int[] dy = {1, -1, 0, 0};

    public static void DFS(int x, int y, boolean[][] vigiada, boolean[][] visitada, int n, int m)
    {
        visitada[x][y] = true;

        for(int d = 0 ; d < 4 ; d++)
        {
            int vx = x + dx[d], vy = y + dy[d];

            if( n < vx || vx <= 0 )
                continue;

            if( m < vy || vy <= 0 )
                continue;

            if( visitada[vx][vy] || vigiada[vx][vy] )
                continue;

            DFS(vx, vy, vigiada, visitada, n, m);
        }
    }

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

        int m = in.nextInt();
        int n = in.nextInt();
        int k = in.nextInt();

        boolean[][] vigiada = new boolean[n + 1][m + 1];
        boolean[][] visitada = new boolean[n + 1][m + 1];

        for(int i = 1 ; i <= k ; i++)
        {
            int x, y;
            char direcao;

            y = in.nextInt();
            x = in.nextInt();
            direcao = in.next().charAt(0);

            if( direcao == 'N' )
            {
                for(int j = 1 ; j <= x ; j++)
                    vigiada[j][y] = true;
            }

            if( direcao == 'S' )
            {
                for(int j = x ; j <= n ; j++)
                    vigiada[j][y] = true;
            }

            if( direcao == 'O' )
            {
                for(int j = 1 ; j <= y ; j++)
                    vigiada[x][j] = true;
            }

            if( direcao == 'L' )
            {
                for(int j = y ; j <= m ; j++)
                    vigiada[x][j] = true;
            }
        }

	if(vigiada[1][1]) {
            System.out.printf("N\n");
	    return;
	}
        DFS(1, 1, vigiada, visitada, n, m);

        if( visitada[n][m] )
            System.out.printf("S\n");
        else
            System.out.printf("N\n");
	}
}

