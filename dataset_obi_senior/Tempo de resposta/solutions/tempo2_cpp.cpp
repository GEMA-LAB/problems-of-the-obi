// OBI2021
// 13186-D
// Letícia Barbieri Stroeh, Colégio Etapa Valinhos
// Tempo de Resposta
// Eu autorizo a OBI a utilizar meu código como desejar

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAXX = 112;
// ult[i] = instante em que i mandou sua mensagem mais recente
// marc[i] = 0: i não aparece na entrada, = 1: i não recebeu resposta para sua mensagem, = 2: i recebeu resposta para sua mensagem
// resp[i] = resposta do problema
// s[i] = letra do evento i
int ult[MAXX], marc[MAXX], resp[MAXX];
char s[MAXN];

int main(){
    
    // t = tempo atual
    int n, t = 0, b;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i ++){
        
        scanf(" %c %d", &s[i], &b);
        
        int flag = 0;
        // se não houver T entre dois eventos, somar 1s no tempo atual e redirecionar para caso certo
        if(i >= 1 && (s[i] == 'R' || s[i] == 'E') && (s[i - 1] == 'R' || s[i - 1] == 'E')){
            t ++;
            if(s[i] == 'R'){
                flag = 1;
            }
            if(s[i] == 'E'){
                flag = 2;
            }
        }
        
        // T: somamar b no tempo atual
        if(s[i] == 'T'){
            t += b;
        }
        
        // R: b envia mensagem no tempo ult[b] = t;
        if(s[i] == 'R' || flag == 1){
            ult[b] = t;
            marc[b] = 1;
        }
        
        // E: b recebe mensagem no tempo t, soma do tempo aumenta em t - ult[b]
        if(s[i] == 'E' || flag == 2){
            resp[b] += t - ult[b];
            marc[b] = 2;
        }
        
    }
    
    for(int i = 0; i < MAXX; i ++){
        
        // se i não recebeu resposta: -1
        if(marc[i] == 1){
            printf("%d -1\n", i);
            continue;
        }
        
        // se i não aparece na entrada, ignorar
        if(marc[i] == 0) continue;
        
        // se i recebeu resposta: resp[i]
        if(marc[i] == 2) printf("%d %d\n", i, resp[i]);
    }
    
}
