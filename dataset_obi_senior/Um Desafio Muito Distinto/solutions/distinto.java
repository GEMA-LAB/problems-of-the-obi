import java.util.Scanner;
public class distinto {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int p = in.nextInt();
		for(int i = 1; i <= p; i++) {
		    long l = in.nextLong();
		    long a = in.nextLong();
		    long b = in.nextLong();
		    if(sum(a, b) < l) System.out.println(b - a + 1);
            else {
                //busca binaria pra encontrar o primeiro cuja soma dá maior ou igual a l
                long ini = a, fim = b;
                while(ini < fim) {
                    long m = (ini + fim)/2;
                    if(sum(a, m) >= l) fim = m;
                    else ini = m + 1;
                }
                System.out.println(ini - a + 1);
            }
		}
	}
	public static long sum(long ini, long fim) {
	    return (ini + fim) * (fim - ini + 1) / 2;
	}
}
