ll exgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if (b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}

// ---
// 引用返回通解: $X = x + k * dx, Y = y – k * dy$\\
// 引用返回的x是最小非负整数解，方程无解函数返回0
// ---
#define Mod(a, b) (((a) % (b) + (b)) % (b))
bool solve(ll a, ll b, ll c, ll& x, ll& y, ll& dx, ll& dy) {
    if (a == 0 && b == 0) return 0;
    ll x0, y0;
    ll d = exgcd(a, b, x0, y0);
    if (c % d != 0) return 0;
    dx = b / d, dy = a / d;
    x = Mod(x0 * c / d, dx);
    y = (c - a * x) / b;
    //  y = Mod(y0 * c / d, dy); x = (c - b * y) / a;
    return 1;
}

// ---
// 利用exgcd求$a$在模$m$下的逆元，需要保证$gcd(a, m) == 1$.
// ---
ll inv(ll a, ll m)
{
    ll x, y;
    ll d = exgcd(a, m, x, y);
    return d == 1 ? (x + m) % m : -1;
}
// ---
// $a < m$ 且 $m$为素数时，有以下两种求法
// ---
ll inv(ll a, ll m) { return a == 1 ? 1 : inv(m % a, m) * (m - m / a) % m; }
ll inv(ll a, ll m) { return Pow(a, m - 2, m); }