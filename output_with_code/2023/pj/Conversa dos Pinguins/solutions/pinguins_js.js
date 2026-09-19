var eA, eB, tA, tB;

scanf("%c %c", "eA", "eB");
scanf("%f %f", "tA", "tB");

if (eA == "F") {
    tA = (tA - 32.0) * 5.0 / 9.0;
}

if (eB == "F") {
    tB = (tB - 32.0) * 5.0 / 9.0;
}

if (tA < tB) {
    printf("A\n");
}
else {
    printf("B\n");
}
