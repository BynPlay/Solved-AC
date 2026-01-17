import sys
input = sys.stdin.readline
from collections import deque

INF = float("inf")

def bfs(N,A,start):
    queue = deque([start])
    visited = set()
    DP = [INF] * N
    DP[start] = 0

    while queue:
        now = queue.popleft()
        nxt = A[now]
        for _ in range(1,nxt+1):
            if(now + _ < N and now + _ not in visited):
                DP[now + _] = DP[now] + 1
                visited.add(now + _)
                queue.append(now + _)

    return DP
            
N = int(input())
A = list(map(int, input().split()))

ans = bfs(N,A,0)[N-1]

if(ans == INF):
    print(-1)
else:
    print(ans)