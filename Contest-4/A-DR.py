PIVOT = 10**9 + 7

n = int(input())
matriz = [input().strip() for _ in range(n)]

dp = [[0] * n for _ in range(n)]

if matriz[0][0] == '.':
    dp[0][0] = 1

for i in range(n):
    for j in range(n):
        if matriz[i][j] == '*':
            continue
        if i > 0:
            dp[i][j] = (dp[i][j] + dp[i-1][j]) % PIVOT
        if j > 0:
            dp[i][j] = (dp[i][j] + dp[i][j-1]) % PIVOT

print(dp[n-1][n-1])
