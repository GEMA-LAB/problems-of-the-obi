#!/usr/bin/env python3

def main():
  
  MAXN = 101
  MAXT = 101
  comprei = [False] * MAXT  # se já comprei fruta desse tipo
  tipo = [0] * MAXN
  preco = [0] * MAXN

  linha = input().split()
  dinheiro = int(linha[0])
  num_frutas = int(linha[1])
  
  for i in range(num_frutas):
    linha = input().split()
    tipo[i] = int(linha[0])
    preco[i] = int(linha[1])
  
  resp = 0

  while True:
    # Procuro a melhor fruta pra comprar
    mais_barata = -1
    for i in range(num_frutas):
      if comprei[tipo[i]]:
        # Comprar tipo repetido é inútil
        continue
      if mais_barata == -1 or preco[i] < preco[mais_barata]:
        mais_barata = i

    # Vejo se já acabou o dinheiro
    if mais_barata == -1 or preco[mais_barata] > dinheiro:
      break

    # Compro a fruta
    resp += 1
    dinheiro -= preco[mais_barata]
    comprei[tipo[mais_barata]] = True
  
  print(resp)

if __name__ == "__main__":
  main()
