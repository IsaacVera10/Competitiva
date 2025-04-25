def reconstruct_path(arr, prev, idx):
    path = []
    while idx != -1:
        path.append(arr[idx])
        idx = prev[idx]
    return path[::-1]

while True:
    line = input()
    if line.strip() == "0":
        break
    data = list(map(int, line.strip().split()))
    n, arr = data[0], data[1:]
    
    dp = [1] * n
    prev = [-1] * n
    
    for i in range(n):
        for j in range(i):
            if arr[j] < arr[i]:
                if dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
                    prev[i] = j
                elif dp[j] + 1 == dp[i]:
                    path1 = reconstruct_path(arr, prev, prev[i])
                    path2 = reconstruct_path(arr, prev, j)
                    if path2 < path1:
                        prev[i] = j
    
    max_len = max(dp)
    candidates = [i for i in range(n) if dp[i] == max_len]
    
    best_idx = candidates[0]
    for idx in candidates[1:]:
        if reconstruct_path(arr, prev, idx) < reconstruct_path(arr, prev, best_idx):
            best_idx = idx
    
    result = reconstruct_path(arr, prev, best_idx)
    print(max_len, *result)
