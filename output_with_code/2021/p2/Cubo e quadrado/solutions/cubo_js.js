// OBI2021 - Fase 3
// Cubo e quadrado

var a, b, resp;

scanf("%d%d", "a", "b");
  
var raiz_cubica = Math.trunc(Math.pow(a,1./3.));
var cubo = raiz_cubica * raiz_cubica * raiz_cubica;
if (cubo < a) {   // raiz_cubica foi truncada, pode ser menor do que a
    raiz_cubica++;
    cubo = raiz_cubica * raiz_cubica * raiz_cubica;
}

//procura por cubos entre a e b, verificando se é também um quadrado
resp = 0;
while (cubo <= b) {
    var raiz_quadrada = Math.trunc(Math.sqrt(cubo));
    var quadrado = raiz_quadrada * raiz_quadrada;
    if (quadrado == cubo) {
	resp++;
    }
    raiz_cubica++;
    cubo = raiz_cubica * raiz_cubica * raiz_cubica;
}

printf("%d\n",resp);

