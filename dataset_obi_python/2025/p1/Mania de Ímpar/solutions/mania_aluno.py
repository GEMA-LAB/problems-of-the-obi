tamanho = input().split()
linhas = int(tamanho[0])
colunas = int(tamanho[1])
cookies = []
for i in range(linhas):
    row = input().split()
    cookies.append([int(x) for x in row])


for i in range(linhas):
    for j in range(colunas):
        if j < colunas - 1:
            if (cookies[i][j] + cookies[i][j+1]) % 2 == 0:
                cookies[i][j+1] += 1  
        if i < linhas - 1:
            if (cookies[i][j] + cookies[i+1][j]) % 2 == 0:
                cookies[i+1][j] += 1  


for i in range(linhas):
    for j in range(colunas):
        if j < colunas - 1:
            print(cookies[i][j], end=" ")
        else:
            print(cookies[i][j])
