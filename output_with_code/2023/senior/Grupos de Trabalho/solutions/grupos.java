import java.util.*;
public class grupos {
  static int[][] juntos = new int[1000010][2];
  static int[][] separados = new int[1000010][2];
  static int[] grupo = new int[1000010];
  
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int e = in.nextInt();
		int m = in.nextInt(); 
		int d = in.nextInt();
		
		for(int i = 1; i <= m; i++) {
		  juntos[i][0] = in.nextInt();
		  juntos[i][1] = in.nextInt();
		}
		
		for(int i = 1; i <= d; i++) {
      separados[i][0] = in.nextInt();
      separados[i][1] = in.nextInt();
		}
		
		for(int i = 1; i <= e/3; i++) {
      int a = in.nextInt();
      int b = in.nextInt(); 
      int c = in.nextInt(); 
      
      grupo[a] = grupo[b] = grupo[c] = i;
    }
    
    int resp = 0;
    for(int i = 1; i <= m; i++)
      if(grupo[juntos[i][0]] != grupo[juntos[i][1]])
        resp++;
    for(int i = 1; i <= d; i++)
      if(grupo[separados[i][0]] == grupo[separados[i][1]])
        resp++;
    
		System.out.println(resp);
	}
}
