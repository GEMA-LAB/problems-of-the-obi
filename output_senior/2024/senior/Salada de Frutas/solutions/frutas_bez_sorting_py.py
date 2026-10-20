#!/usr/bin/env python3

def main():
  linha = input().split()
  dinheiro = int(linha[0])
  num_frutas = int(linha[1])
  
  frutas = []
  for _ in range(num_frutas):
    linha = input().split()
    tipo = int(linha[0])
    preco = int(linha[1])
    frutas.append((preco, tipo))
  
  # Ordena por preço
  frutas.sort()
  
  # Se já comprei fruta desse tipo
  comprei = [False] * 101
  resp = 0
  
  for preco, tipo in frutas:
    if comprei[tipo]:
      # Comprar tipo repetido é inútil
      continue
    if preco > dinheiro:
      # Todos daqui pra frente vão ser mais caros do que meu dinheiro
      break
    # Compro a fruta
    resp += 1
    dinheiro -= preco
    comprei[tipo] = True
  
  print(resp)

if __name__ == "__main__":
  main()
