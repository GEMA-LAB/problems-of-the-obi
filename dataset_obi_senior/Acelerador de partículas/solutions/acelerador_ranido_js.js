//
// problema acelerador, OBI2020
//

var d, resto;

scanf("%d","d");

d -= 3;
resto = d % 8;

if (resto == 3)
    printf("1\n");
else if (resto == 4)
    printf("2\n");
else
    printf("3\n");

