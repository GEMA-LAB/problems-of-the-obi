import java.util.Scanner;
public class placar {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int[] gols = new int[110];
		int p = in.nextInt();
		for(int i = 1; i <= p; i++) {
		    int t = in.nextInt();
		    gols[t] = 1;
		}
		int c = in.nextInt();
		for(int i = 1; i <= c; i++) {
		    int t = in.nextInt();
		    gols[t] = 2;
		}
		int[] placar = new int[3];
		System.out.println(placar[1] + " " + placar[2]);
		for(int t = 1; t <= 100; t++) {
		    if(gols[t] != 0) {
		        placar[gols[t]]++;
		        System.out.println(placar[1] + " " + placar[2]);
		    }
		}
	}
}