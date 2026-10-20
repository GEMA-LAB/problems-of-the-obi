#!/usr/bin/env python3

def main():
    k,n,m=map(int, input().split())
    graph=[[] for i in range(n+1)]
    for i in range(m):
        a,b,c,d=map(int, input().split())
        graph[a].append([b,c,d])       
        graph[b].append([a,c,d])       
    s,t=map(int, input().split())
    dp=[[1555555555 for j in range(k+1)]for i in range(n+1)]       # 2D array called dp to store the answers
    for i in range(k+1):
        dp[s][i]=0                     # distance from the source to the source is definitely 0
    flag=[False for i in range(n+1)]   # flag to prevent pushing the same node onto the queue when the node is already in the queue
    q=[s]
    while q:
        u=q.pop(0)
        flag[u]=False
        for v in graph[u]:
            for i in range(k-v[2]+1):
                if dp[u][i]+v[1]<dp[v[0]][i+v[2]]:
                    dp[v[0]][i+v[2]]=dp[u][i]+v[1]
                    if not flag[v[0]]:
                        q.append(v[0])
                        flag[v[0]]=True
    if dp[t][k-1]>1e9:
        print(-1)
    else:
        print(dp[t][k-1])
        
main()
