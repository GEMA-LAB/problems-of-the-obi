/*
OBI 2024 - Fase 3
	Hotel Nlogônia
	Solução em O(N log N) com Two Pointers + Sets (ou "Sliding Window")
*/

import java.util.*;
import java.io.*;

public class hotel {
  public static void main(String[] args) {
    Scanner stdin = new Scanner(System.in);
    
    int n = stdin.nextInt();
    int d = stdin.nextInt();
    long w = stdin.nextInt();
    int[] p = new int[n + 1];

    // somas parciais:
	// psum guarda somas de prefixo;
	// dsum guarda somas de intervalos de tamanho D
    long[] psum = new long[n + 1];
    long[] dsum = new long[n + 1];
    psum[0] = 0;
    dsum[0] = 0;
    for (int i = 1; i <= n; i++) {
        p[i] = stdin.nextInt();
        psum[i] = psum[i - 1] + p[i];
        if (i >= d) {
            dsum[i] = psum[i] - psum[i - d];
        } else {
            dsum[i] = 0;
        }
    }

  	// técnica de two pointers para encontrar o maior intervalo válido
    int resp = d;
    long cur_tot = psum[d - 1]; // soma da janela atual
    int l = 1;

    // vamos guardar todas as somas para intervalos de tamanho D na
	// janela atual do two pointers, ordenados decrescente por soma,
	// em um map para inserção/consulta do maior em O(log N);
	// usamos um map ao invés de um set pois podem haver elementos
	// repetidos (o map é { valor -> quantas vezes ele está no set })
    TreeMap<Long, Integer> dsums = new TreeMap<>(); 
    
    for (int r = d; r <= n; r++) {
    	// adiciona r na janela do two pointers
        cur_tot += p[r];
        dsums.put(dsum[r], dsums.getOrDefault(dsum[r], 0) + 1);

    	// enquanto o custo estiver muito alto, remove l da janela do two pointers
        boolean ok = false;
        while (!ok) {
            if (r - l + 1 <= d) ok = true;
            else {
                long largest_dsum = dsums.lastKey();
                ok = (cur_tot - largest_dsum <= w);
            }
            if (ok) break;

            cur_tot -= p[l];
            long val_to_modify = dsum[l + d - 1];
            dsums.put(val_to_modify, dsums.get(val_to_modify) - 1);
            if (dsums.get(val_to_modify) == 0) {
                dsums.remove(val_to_modify);
            }
            l++;
        }
        resp = Math.max(resp, r - l + 1);
    }
    System.out.println(resp);
  }
}