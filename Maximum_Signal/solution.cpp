def can(a, n, k, target):
    for pos in range(n - 1):
        if a[pos] >= target:
            return True
        t = a[:]
        t[pos] = target
        ok = True
        for j in range(pos, n - 1):
            if t[j] > a[j]:
                if t[j] - 1 > t[j + 1]:
                    t[j + 1] = t[j] - 1
        if t[n - 1] > a[n - 1]:
            ok = False
        if not ok:
            continue
        need = 0
        for j in range(pos, n - 1):
            need += t[j] - a[j]
            if need > k:
                break
        if need <= k:
            return True
    return False

def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    
    lo = max(a)
    hi = max(a) + k
    ans = lo
    
    while lo <= hi:
        mid = (lo + hi) // 2
        if can(a, n, k, mid):
            ans = mid
            lo = mid + 1
        else:
            hi = mid - 1
    
    print(ans)

tst = int(input())
for _ in range(tst):
    solve()