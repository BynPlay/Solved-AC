import sys
input = sys.stdin.readline
from collections import deque

dx = [1,-1,0,0] 
dy = [0,0,-1,1]

def bfs(table,start):
    visited = set()
    queue = deque([start])
    visited.add(start)

    while queue:
        now_y, now_x = queue.popleft()
        if(now_y == M-1):
            return 'YES'
        for i in range(4):
            if(0 <= now_x + dx[i] < N and 0 <= now_y + dy[i] < M and (now_y + dy[i], now_x + dx[i]) not in visited and table[now_y + dy[i]][now_x + dx[i]] == 0):
                queue.append((now_y + dy[i], now_x + dx[i]))
                visited.add((now_y + dy[i], now_x + dx[i]))
    
    return 'NO'

M, N = map(int, input().split()) 
table = [list(map(int, input().strip())) for _ in range(M)]  

check = False

for _ in range(N):
    if(bfs(table,(0,_)) == 'YES'):
        check = True
        print('YES')
        break

if(check == False):
    print('NO')
    