namespace ExLucas {
    ll mul(ll a, ll b, ll p) {
        return (a * b - (ll)((long double)a / p * b) * p + p) % p;
    }

    ll quick(ll a, ll b, ll p) {
        ll sum = 1;
        while(b) {
            if(b & 1) sum = sum * a % p;
            a = a * a % p;
            b >>= 1;
        }
        return sum;
    }

    ll exgcd(ll a, ll b, ll& x, ll& y) {
        if(b == 0) {
            x = 1, y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, x, y);
        ll z = x;
        x = y;
        y = z - y * (a / b);
        return d;
    }

    ll inv(ll n, ll p) {
        ll x, y;
        ll d = exgcd(n, p, x, y);
        return (x % p + p) % p;
    }

    ll a[20], m[20];

    ll crt(int n) {
        ll M = 1; for(int i = 1; i <= n; ++i) M *= m[i];
        ll x, y, d, Mi, ans = 0;
        for(int i = 1; i <= n; ++i)
        {
            Mi = M / m[i];
            d = exgcd(Mi, m[i], x, y);
            x = (x % M + M) % M;
            ans = (ans + mul(mul(a[i], Mi, M), x, M)) % M;
        }
        return (ans % M + M) % M;
    }

    ll getNumofP(ll n, ll p) {
        ll cnt = 0; while(n) cnt += (n /= p);
        return cnt;
    }

    ll getWithoutP(ll n, ll p, ll P) {
        if(n == 0) return 1;
        ll g = 1, T = n / P, Y = n % P;
        for(int i = 1; i <= P - 1; ++i) if(i % p) g = g * i % P;
        g = quick(g, T, P);
        for(int i = 1; i <= Y; ++i) if(i % p) g = g * i % P;
        return g * getWithoutP(n / p, p, P) % P;
    }

    ll calMod(ll n, ll m, ll p, ll P) {
        ll p0 = mul(mul(getWithoutP(n, p, P), inv(getWithoutP(n - m, p, P), P), P), inv(getWithoutP(m, p, P), P), P);
        ll p1 = quick(p, getNumofP(n, p) - getNumofP(n - m, p) - getNumofP(m, p), P);
        return mul(p0, p1, P);
    }

    ll exLucas(ll n, ll k, ll p) {
        ll cnt = 0;
        for(int i = 2; 1ll * i * i <= p; ++i) {
            if(p % i == 0) {
                ll P = 1;
                while(p % i == 0) P *= i, p /= i;
                ++cnt, m[cnt] = P, a[cnt] = calMod(n, k, i, P);
            }
        }
        if(p > 1) ++cnt, m[cnt] = p, a[cnt] = calMod(n, k, p, p);
        return crt(cnt);
    }
}
