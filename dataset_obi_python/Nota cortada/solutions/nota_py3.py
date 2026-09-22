#!/usr/bin/env python3

# Calculando explicitamente a area de Felix (um triangulo mais um retangulo)
# e comparando com a metade da area original da nota: 5600 = (160/2)*70


B = int(input())
T = int(input())

altura = 70;
base = abs(B-T);
triangulo = (base*altura)/2 # sera sempre inteiro

retangulo = min(B,T)*altura;
felix = triangulo+retangulo;

if felix > 5600:
    print('1')
elif felix < 5600:
    print('2')
else:
    print('0')
