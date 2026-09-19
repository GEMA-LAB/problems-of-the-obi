/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - modela os grupos de amigos como componentes conexas
      de um grafo. Faz DFS para identificar os grupos de amigos
    - usa vetor de marcação para ver se alguma componente
      aparece mais de uma vez em uma entrevista
*/

import java.util.*;
import java.io.*;

public class entrevistas_dfs_mrk_java {
    static int n;
    static char[][] tabela;
    static int[] componente;

    static void DFS(int v, int c) {
        componente[v] = c;
        for (int w = 0; w < n; w++) {
            if (tabela[v][w] == '0' || componente[w] != 0) continue;
            DFS(w, c);
        }
    }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(
        new InputStreamReader(System.in));
    
    n = Integer.parseInt(br.readLine());
    tabela = new char[n][];
    componente = new int[n];

    for (int i = 0; i < n; i++) {
        tabela[i] = br.readLine().toCharArray();
    }

    for (int i = 0; i < n; i++) {
        componente[i] = 0;
    }
    int cur_comp = 1;
    for (int i = 0; i < n; i++) {
        if (componente[i] == 0) {
            DFS(i, cur_comp);
            cur_comp++;
        }
    }

    boolean[] mrk = new boolean[n + 1];
    for (int i = 0; i <= n; i++) {
        mrk[i] = false;
    }

    int e = Integer.parseInt(br.readLine());
    int[] candidato = new int[n];
    while (e > 0) {
        e--;
        String[] line = br.readLine().split(" ");
        int k = Integer.parseInt(line[0]);

        boolean possui_amigos = false;

        for (int i = 0; i < k; i++) {
            // estamos indexando do zero
            candidato[i] = Integer.parseInt(line[i + 1]) - 1;
        }

        for (int i = 0; i < k; i++) {
            if (mrk[componente[candidato[i]]]) {
                possui_amigos = true;
            }
            mrk[componente[candidato[i]]] = true;
        }

        for (int i = 0; i < k; i++) {
            mrk[componente[candidato[i]]] = false;
        }

        if (possui_amigos) {
            System.out.println("S");
        } else {
            System.out.println("N");
        }
    }
  }
}
