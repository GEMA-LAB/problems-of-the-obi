// OBI2021 - Fase 2
// Anagrama

import java.util.Scanner;

public class anagrama {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int[] letras1=new int[26];
    int[] letras2=new int[26];
    int n;
    String linha;

    n = in.nextInt();
    linha = in.nextLine();
    linha = in.nextLine();
    for (int i=0; i<n; i++) {
	char c = linha.charAt(i);
	if (c != ' ' && c != ',' && c != '.')
	    letras1[(c - 'a')]++;
    }
    linha = in.nextLine();
    for (int i=0; i<n; i++) {
	char c = linha.charAt(i);
	if (c != ' ' && c != ',' && c != '.')
	    letras2[(c - 'a')]++;
    }
    char res = 'S';
    for (int i=0; i<26; i++) {
	if (letras1[i] != letras2[i]) {
	    res = 'N';
	}
    }
    System.out.println(res);
  }
}
