import sys
input = sys.stdin.readline

T_cases = int(input())

MAX_N = 1000
DP = [[0] * 10 for _ in range(MAX_N + 1)]
MOD = 1234567

adj = [[7], [2, 4], [1, 3, 5], [2, 6], [1, 5, 7], 
       [2, 4, 6, 8], [3, 5, 9], [4, 8, 0], [5, 7, 9], [6, 8]]

for i in range(10):
    DP[1][i] = 1

for i in range(1, MAX_N):
    for j in range(10):
        for k in adj[j]:
            DP[i+1][k] = (DP[i+1][k] + DP[i][j]) % MOD

for _ in range(T_cases):
    N = int(input().strip())
    print(sum(DP[N]) % MOD)