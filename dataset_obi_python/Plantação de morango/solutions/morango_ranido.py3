#!/usr/bin/env python3
# solução para o problema "Plantação de morangos"

# lê a entrada
larg1 = int(input())
comp1 = int(input())
larg2 = int(input())
comp2 = int(input())

# calcula as áreas
a1 = larg1 * comp1  
a2 = larg2 * comp2  

# calcula e escreve o resultado
if a1 >= a2:        
    print(a1)
else:
    print(a2)


