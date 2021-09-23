template<typename T>
struct BZ {
	const static int K = 25, Ma = 1e6;
	const std::vector<std::vector<T>>& g;
	int f[Ma][K + 1], dep[Ma];
	void dfs(int u) {
		for (const auto& i : g[u]) if (!dep[i])
			dep[i] = dep[u] + 1, f[i][0] = u, dfs(i);
	}
	BZ(std::vector<std::vector<T>>& g, int n, int rt = 0) : g(g) {
		memset(dep, 0, sizeof dep);
		dep[rt] = 1; f[rt][0] = rt;
		dfs(rt);
		for (int i = 1; i <= K; i++) 
			for (int j = 0; j < n; j++)
				f[j][i] = f[f[j][i - 1]][i - 1];
	}
	int lca(int a, int b) {
		if (dep[a] < dep[b]) std::swap(a, b);
		for (int i = K; i >= 0; i--)
			if (dep[f[a][i]] >= dep[b])
				a = f[a][i];
		if (a == b) return a;
		for (int i = K; i >= 0; i--)
			if (f[a][i] != f[b][i])
				a = f[a][i], b = f[b][i];
		return f[a][0];
	}
};