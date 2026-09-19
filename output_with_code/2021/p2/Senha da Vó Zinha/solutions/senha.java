// OBI2021 - Fase 2
// Senha

import java.util.Arrays;
import java.util.Scanner;

public class senha {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int n, m, k, x, tmp=0;
	
	n = in.nextInt();
	m = in.nextInt();
	k = in.nextInt();
	char[] s = new char[n];
	char[][] palavras = new char[m][m];
	int[] pos = new int[n];


	s = in.next().toCharArray();
	for (int i = 0; i < n; i++)
	    if (s[i] == '#')
		pos[tmp++] = i;
	for (int i = 0; i < m; i++)
	    palavras[i] = in.next().toCharArray();
	x = in.nextInt();

	if (m == 1) {
	    Arrays.sort(palavras[0], 0, k);
	    s[pos[0]] = palavras[0][x - 1];
	    System.out.println(s);
	}
	else {
	    x--;
	    for (int i = 0; i < m; i++)
		Arrays.sort(palavras[i], 0, k);
	    for (int i = 0; i < m; i++)
		s[pos[i]] = palavras[i][0];
	    for (int i = m - 1; i >= 0; i--) {
		if (x == 0)
		    break;
		tmp = x % k;
		s[pos[i]] = palavras[i][tmp];
		x /= k;
	    }
	    System.out.println(s);
	}
    }
}
