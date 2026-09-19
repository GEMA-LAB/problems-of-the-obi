//
// problema caixas, OBI2020
//

scanf("%d", "a");
scanf("%d", "b");
scanf("%d", "c");


if (a < b)
    if (b < c)
        printf("1\n");
    else
        printf("2\n");
else if (b < c)
    if (a+b < c)
        printf("1\n");
    else
	printf("2\n");
else
    printf("3\n");
