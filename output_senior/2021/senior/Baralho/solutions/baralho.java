import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class baralho {

    public static void main(String[] args) {
        BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
        String linha="";
        ArrayList<String> cartas=  new ArrayList<>();
        String carta;
        int C = 13;
        int E = 13;
        int U = 13;
        int P = 13;

	linha = teclado.readLine();

        for (int i = 0; i < linha.length(); i++) {
            if ("CEUP".indexOf(linha.charAt(i))>-1)
            {
                carta = linha.substring(0,linha.indexOf(linha.charAt(i))+1);
                linha = linha.substring(linha.indexOf(linha.charAt(i))+1);
                char naipe = carta.charAt(2);

                switch (naipe){
                    case 'C':
                        if (!cartas.contains(carta)) {
                            cartas.add(carta);
                            C--;
                        }
                        else
                            C = -1;
                        break;
                    case 'E':
                        if (!cartas.contains(carta)) {
                            cartas.add(carta);
                            E--;
                        }
                        else
                            E = -1;
                        break;
                    case 'U':
                        if (!cartas.contains(carta)) {
                            cartas.add(carta);
                            U--;
                        }
                        else
                            U = -1;
                        break;
                    case 'P':
                    if (!cartas.contains(carta)) {
                        cartas.add(carta);
                        P--;
                    }
                    else
                        P = -1;
                    break;
                }
                        i=0;
            }
        }
        System.out.println(C>=0?C:"erro");
        System.out.println(E>=0?E:"erro");
        System.out.println(U>=0?U:"erro");
        System.out.println(P>=0?P:"erro");
    }
}
