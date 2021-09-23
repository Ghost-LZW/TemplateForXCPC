inline ll mul(ll a, ll b, ll mod) {
    if (mod <= 1000000000)
        return a * b % mod;
    else if (mod <= 1000000000000ll)
        return (((a * (b >> 20) % mod) << 20) + (a * (b & ((1 << 20) - 1)))) % mod;
    else {
        ll d = (ll)floor(a * (long double)b / mod + 0.5);
        ll ret = (a * b - d * mod) % mod;
        if (ret < 0) ret += mod;
        return ret;
    }
}