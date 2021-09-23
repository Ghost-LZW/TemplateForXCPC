ll Euler(ll n) {
    ll rt = n;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            rt -= rt / i;
            while (n % i == 0) n /= i;
        }
    if (n > 1) rt -= rt / n;
    return rt;
}

int phi[Ma] = {0, 1};
void CalEuler(){
    for (int i = 2; i < Ma; i++)
        if (!phi[i])
            for (int j = i; j < Ma; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
}