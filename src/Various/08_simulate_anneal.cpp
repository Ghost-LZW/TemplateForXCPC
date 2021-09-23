constexpr db dt = 0.996;

int cal();

inline void simulate_anneal(int& ans) {
	db t = 3000;
	static int buf[Ma];
	memcpy(buf, ck, sizeof ck);
	while (t > 1e-15) {
		int x = rand() % cnt;
		int y = rand() % cnt;
		swap(buf[x], buf[y]);
		int now = cal(buf);
		int delta = now - ans;
		if (delta < 0) {
			memcpy(ck, buf, sizeof buf);
			ans = now;
		} else if (exp(-delta / t) * RAND_MAX > rand()) swap(buf[x], buf[y]);
		t *= dt;
	}
}

inline int solve() {
	int ans = cal(ck);
	while ((db)clock() / CLOCKS_PER_SEC <= 0.6) simulate_anneal(ans);
	return ans;
}