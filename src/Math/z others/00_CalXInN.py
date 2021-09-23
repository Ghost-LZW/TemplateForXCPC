def cal(n, x) :
    now, ans = 1, 0
    while n >= now :
        k = n // now
        ans += (k // 10) * now
        cur = k % 10
        if cur > x :
            ans += now
        elif cur == x :
            ans += n - k * now + 1
        now *= 10
    return ans