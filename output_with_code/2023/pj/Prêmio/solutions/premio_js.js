// OBI2023
// Tarefa Prêmio
// r. anido


var pao, doce, bolo;

scanf("%d", "pao");
scanf("%d", "doce");
scanf("%d", "bolo");


var pontos = pao + 2*doce + 3*bolo;
		
if (pontos >= 150) 
    printf("B\n");
else if (pontos >= 120)
    printf("D\n");
else if (pontos >= 100)
    printf("P\n");
else
    printf("N\n");

