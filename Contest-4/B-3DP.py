n = int(input())

dp = [0, 0, 0, 1]

MOD = 10**9 + 7
for _ in range(n):
    a, b, c, d = dp
    dp = [
        (b + c + d) % MOD,#A
        (a + c + d) % MOD,#B
        (a + b + d) % MOD,#C
        (a + b + c) % MOD #D
    ]

print(dp[3])
