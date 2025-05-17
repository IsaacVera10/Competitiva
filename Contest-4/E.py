n = int(input())
for _ in range(n):
    s = input().strip()
    digits = [int(c) for c in s]
    total = sum(digits)
    mods = {total % 9}

    for d in digits:
        if d in {0, 1, 2, 3}:
            sq = d * d
            delta = sq - d
            new_mods = set()
            for m in mods:
                new_mods.add((m + delta) % 9)
            mods.update(new_mods)

    print("YES" if 0 in mods else "NO")
