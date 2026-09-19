// OBI2021
// retangulo
import java.io.BufferedReader; 
import java.io.IOException; 
import java.io.InputStreamReader; 
import java.util.Scanner; 
import java.util.StringTokenizer;

public class ranido_java2 {

    public static final int MAXN = 100000;
    public static int n;
    public static int[] trees;
    public static int arc_sum=0, half_circ, p=0, q=0, np=0, i;

    public static void main(String[] args) throws IOException {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	n = Integer.parseInt(br.readLine());
	trees = new int[n];
	StringTokenizer st = new StringTokenizer(br.readLine());
	for (int i=0; i<n; i++) {
	    trees[i] = Integer.parseInt(st.nextToken());
	    arc_sum = arc_sum + trees[i];
	}
	if (arc_sum % 2 == 1) {
	    System.out.printf("N\n");
	    return;
	}
	half_circ = arc_sum/2;
	arc_sum = 0;
	//procura por dois pares de pontos diametralmente opostos
	while (q != n && np < 2) {
	    if (arc_sum < half_circ) {  //avança q
		arc_sum = arc_sum + trees[q];
		q++;
	    }
	    else if (arc_sum > half_circ) { // avança p
		arc_sum = arc_sum - trees[p];
		p++;
	    }
	    else {  // avança  p e q
		arc_sum = arc_sum - trees[p] + trees[q];
		p++; q++; 
		//if (arc_sum > 0) 
		np++;
	    }
	}
	if (np >= 2)
	    System.out.printf("S\n");
	else
	    System.out.printf("N\n");
    }
}
