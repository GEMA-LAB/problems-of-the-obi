var msg1;
var divertido = ":-)";
var chateado = ":-(";
var num_divertido = 0;
var num_chateado = 0;


var c;
scanf("%c","c");
while (c != '\n') {
	msg1 += c;
	scanf("%c","c");
}
var msg2 = msg1;

i = msg1.indexOf(divertido);
while (i != -1) {
   num_divertido++;
   msg1 = msg1.substring(i+3);
   i = msg1.indexOf(divertido);
}
i = msg2.indexOf(chateado);
while (i != -1) {
   num_chateado++;
   msg2 = msg2.substring(i+3);
   i = msg2.indexOf(chateado);
}

if (num_divertido > num_chateado)
   printf("divertido\n");
else if (num_divertido < num_chateado)
      printf("chateado\n");
   else
      printf("neutro\n");

