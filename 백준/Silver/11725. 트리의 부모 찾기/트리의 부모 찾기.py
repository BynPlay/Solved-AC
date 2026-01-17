import sys
input = sys.stdin.readline
from collections import deque

def bfs(Tree):
    queue = deque([1])
    visited = [False] * (N+1)
    parent = [0] * (N+1)
    visited[1] = True
    
    while queue:
        now = queue.popleft()
        for i in Tree[now]:
            if not visited[i]: 
                visited[i] = True
                parent[i] = now
                queue.append(i)

    return parent

N = int(input())

Tree = [[] for i in range(N+1)]

for _ in range(N-1):
    a, b = map(int,input().split())
    Tree[a].append(b)
    Tree[b].append(a)

parent = bfs(Tree)
for i in range(2, N+1):
    print(parent[i])
