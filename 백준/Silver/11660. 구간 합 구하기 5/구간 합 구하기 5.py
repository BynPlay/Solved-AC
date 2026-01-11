import sys
input = sys.stdin.readline

N,M = map(int, input().split())

matrix = [[0] * (N + 1)] 
for _ in range(N):
    matrix.append([0] + list(map(int, input().split())))

DP = [[0 for _ in range(N+1)] for _ in range(N+1)]

for n in range(1,N+1):
    DP[1][n] = DP[1][n-1] + matrix[1][n]
    
for i in range(2,N+1):
    for j in range(1,N+1):
        DP[i][j] = DP[i-1][j] + DP[i][j-1] - DP[i-1][j-1] + matrix[i][j]
        
for _ in range(M):
    x1, y1, x2, y2 = map(int, input().split())
    print(DP[x2][y2] - DP[x1-1][y2] - DP[x2][y1-1] + DP[x1-1][y1-1])