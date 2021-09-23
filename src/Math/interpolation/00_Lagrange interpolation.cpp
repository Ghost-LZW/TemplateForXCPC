inline int lagrange(int *x, int *y, int k){
	int ans = 0;
	for(int i = 0; i < n; ++i) {
		int ell = 1;
		for(int j = 0; j < n; ++j) {
			if(i == j) continue;
			ell = 1ll * ell * (k - x[j]) % mod * quick_power(x[i] - x[j], mod - 2) % mod;
		}
		ans = (ans + 1ll * y[i] * ell) % mod;
	}
	return ans;
}

// 连续取值

int lagrange(int n, int *y, int k) {
    pre[0] = suf[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = 1LL * pre[i - 1] * (k - i) % mod;
    }
    for (int i = n; i >= 1; i--) {
        suf[i] = 1LL * suf[i + 1] * (k - i) % mod;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int a = 1LL * pre[i - 1] * suf[i + 1] % mod * inv[i - 1] % mod * inv[n - i] % mod;
        if ((n - i) & 1) a = mod - a;
        add(ans, 1LL * a * y[i] % mod);
    }
    return ans;
}