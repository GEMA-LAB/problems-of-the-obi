#!/usr/bin/env python3

def main():
  n = int(input())
  instrucoes = input()

  sala = 1

  # passa pelas instruções em ordem, atualizando a sala a cada passo
  for instrucao in instrucoes:
    if instrucao == 'E':
      sala = 2 * sala
    else:
      sala = 2 * sala + 1

  print(sala)

if __name__ == "__main__":
  main()
