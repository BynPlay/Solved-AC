
N = int(input())

Card = [0] + list(map(int, input().split()))

INF = float('inf')
DP = [INF] * (N + 1)

DP[0] = 0
DP[1] = 1

if(N > 1):
    for i in range(1,N+1):
        DP[i] = DP[i-1] + 1 # i번째 카드를 따로
        for j in range(1,N):
            if(Card[j] >= i - j + 1):
                DP[i] = min(DP[j-1] + 1,DP[i]) # i 번째 카드가 포함
                break
    
print(DP[N])