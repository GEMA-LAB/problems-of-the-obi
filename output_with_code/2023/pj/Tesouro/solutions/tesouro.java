import java.util.*;
public class tesouro
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		char[][] mapa = new char[1010][1010];
    int[][] marc = new int[1010][1010];
		int m;
		m = in.nextInt();
		for(int i = 1; i <= m; i++) {
      String s = in.next();
      for(int j = 0; j < s.length(); j++)
        mapa[i][j + 1] = s.charAt(j);
		}
		int l, c;
		l = in.nextInt();
		c = in.nextInt();
		int resp = -1;
    while(true) {
      if(l < 1 || l > m || c < 1 || c > m) {
        resp = -1;
        break;
      }
      
      if(marc[l][c] == 1) {
        resp = 0;
        break;
      }
    
      marc[l][c] = 1;
      resp++;
      
      if(mapa[l][c] == 'X') break;
      
      if(mapa[l][c] == 'N') l--;
      else if(mapa[l][c] == 'S') l++;
      else if(mapa[l][c] == 'O') c--;
      else c++;
    }
    System.out.println(resp);
	}
}
