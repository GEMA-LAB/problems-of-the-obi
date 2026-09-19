var hrs, minu, secs, t;
scanf("%d", "hrs");
scanf("%d", "minu");
scanf("%d", "secs");
scanf("%d", "t");

secs += t;
minu += (secs / 60);
secs %= 60;
hrs += (minu / 60);
minu %= 60;
hrs %= 24;

printf("%d\n%d\n%d\n", hrs, minu, secs);
