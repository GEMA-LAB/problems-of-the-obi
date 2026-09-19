#!/usr/bin/env python3

def main():
    from queue import PriorityQueue

    [L, C, T] = [int(x) for x in input().split()]

    grid = [[]] * L

    for i in range(L):
        grid[i] = [int(x) for x in input().split()]


    [L1, C1] = [int(x) for x in input().split()]
    L1 -= 1
    C1 -= 1
    [L2, C2] = [int(x) for x in input().split()]
    L2 -= 1
    C2 -= 1

    lo = 0
    hi = 1000000000
    while(lo + 1 < hi):
        mid = (lo + hi) // 2
        caminhoMinimo = 0
        dijkstra = PriorityQueue()
        vis = [[False for j in range(C)] for i in range(L)]
        dist = [[-1 for j in range(C)] for i in range(L)]
        dist[L1][C1] = grid[L1][C1] * mid
        dijkstra.put((dist[L1][C1], [L1, C1]))

        dir = [[0,1],[1,0],[0,-1],[-1,0]]
        while(not dijkstra.empty()):
            [val, [X,Y]] = dijkstra.get()
            vis[X][Y] = True
            for [dx, dy] in dir:
                a = X + dx
                b = Y + dy
                if(a < 0 or a >= L):
                    continue
                if(b < 0 or b >= C):
                    continue
                if(grid[a][b] == -1):
                    continue
                if(vis[a][b] == True):
                    continue
                if(dist[a][b] == -1 or dist[a][b] > dist[X][Y] + grid[a][b] * mid):
                    dist[a][b] = dist[X][Y] + grid[a][b] * mid
                    dijkstra.put((dist[a][b], [a,b]))

        caminhoMinimo = dist[L2][C2] - grid[L2][C2] * mid
        if(caminhoMinimo > T):
            hi = mid
        else:
            lo = mid
    bombons = lo

    print(bombons)

if __name__ == "__main__":
    main()
