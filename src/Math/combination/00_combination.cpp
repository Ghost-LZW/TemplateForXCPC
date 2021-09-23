namespace N_20000 {
	const int Ma = 5000;

	int C[Ma][Ma];

	void init() {
		for (int i = 0; i < Ma; i++)
			for (int j = 0; j <= i; j++)
				if (!j) C[i][j] = 1;
				else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
}

namespace N_1e8 {
template<typename T>
T inverse(T a, T m) {
	T u = 0, v = 1;
	while (a != 0) {
		T t = m / a;
		m -= t * a;
		std::swap(a, m);
		u -= t * v;
		std::swap(u, v);
	}
	assert(m == 1);
	return u;
}
const int Ma = 10000;
const long long mod = 1e9 + 7;
long long fac[Ma], inv[Ma];
long long normalize(long long x) {
	if (x < -mod or x >= mod) x %= mod;
	return x < 0 ? x + mod : x;
}
void init() {
	fac[0] = inv[0] = 1;
	for (int i = 1; i < Ma; i++) fac[i] = fac[i - 1] * i % mod;
	inv[Ma - 1] = inverse(fac[Ma - 1], mod);
	for (int i = Ma - 2; i > 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
}
long long C(int n, int m) {
	if (m > n) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
}

namespace LUCAS {
	typedef __int128 lll;
	typedef long long ll;
	ll p;

	struct Kasumul {
	    ll p, m;
		inline ll normalize(ll x) {
			if (x < -p or x >= p) x %= p;
			return x < 0 ? x + p : x;
	    }
	    Kasumul(ll tp) : p(tp), m((1ll << 60) / tp) {}
	    ll calc(ll x) {
	        ll q = (lll(x) * m) >> 60;
	        ll ans = x - q * p;
	       	return normalize(ans);
	    }
	};

	Kasumul muler(p);

	inline ll normal(ll x) {
		if (x < -p or x >= p) return (*muler).calc(x);
		return x < 0 ? x + p : x;
	}

	inline ll add(ll a, ll b) {
		return normal(a + b);
	}

	inline ll sub(ll a, ll b) {
		return normal(a - b);
	}

	inline ll mul(ll a, ll b) {
		return normal(a * b);
	}

	inline long long Lucas(long long n, long long m) {
		if (m == 0) return 1;
		return mul(C(normal(n), normal(m)), Lucas(n / p, m / p));
	}
}