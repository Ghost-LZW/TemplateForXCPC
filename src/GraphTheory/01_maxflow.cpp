#define qxx(i,x) for(int i=head[x];~i;i=node[i].nex)

template<typename T>
struct EK { // 朴素最大流 O(nm^2)
	static const int Ma = 1e6;
	struct Node {
		int u, v, nex; T w;
	} node[Ma * 2];
	int head[Ma], cnt, n, fa[Ma]; T A[Ma];
	EK(int n=Ma) : n(n) {
		cnt = 0;
		memset(head, -1, sizeof(int) * n);
	}
	void add_edge(int u, int v, T w) {
		node[cnt].u = u, node[cnt].v = v, node[cnt].w = w;
		node[cnt].nex = head[u], head[u] = cnt++;
	}
	void add(int u, int v, T w) {
		add_edge(u, v, w);
		add_edge(v, u, 0);
	}
	T maxflow(int s, int t) {
		T ans = 0;
		for (;;) {
			memset(A, 0, sizeof(T) * n);
			queue<int> q;
			q.emplace(s);
			A[s] = numeric_limits<T>::max();
			while (!q.empty()) {
				int top = q.front(); q.pop();
				qxx(i, top) {
					int v = node[i].v; T w = node[i].w;
					if (!A[v] and w) {
						fa[v] = i;
						A[v] = min(A[top], w);
						q.emplace(v);
					}
				}
				if (A[t]) break; 
			}
			if (!A[t]) break;
			for (int i = t; i != s; i = node[fa[i]].u) {
				node[fa[i]].w -= A[t];
				node[fa[i]^1].w += A[t];
			}
			ans += A[t];
		}
		return ans;
	}
};

template<typename T>
struct Dinic { // O(n^2m)
	static const int Ma = 1e6;
	struct Node {
		int u, v, nex; T w;
	} node[Ma * 2];
	int head[Ma], cnt, n, cur[Ma], d[Ma]; T A[Ma];
	Dinic(int n=Ma) : n(n) {
		cnt = 0;
		memset(head, -1, sizeof(int) * n);
	}
	void add_edge(int u, int v, T w) {
		node[cnt].u = u, node[cnt].v = v, node[cnt].w = w;
		node[cnt].nex = head[u], head[u] = cnt++;
	}
	void add(int u, int v, T w) {
		add_edge(u, v, w);
		add_edge(v, u, 0);
	}
	bool bfs(const int& s, const int& t) {
		memset(d, 0, sizeof(int) * n);
		queue<int> q; q.emplace(s); d[s] = 1;
		while (!q.empty()) {
			int tp = q.front(); q.pop();
			qxx (i, tp) if (node[i].w and !d[node[i].v]) {
				d[node[i].v] = d[tp] + 1;
				q.emplace(node[i].v);
			}
		}
		return d[t];
	}
	T dfs(int u, const int& t, T mn) {
		if (u == t or mn == 0) return mn;
		T flow = 0;
		for (int& i = cur[u]; ~i; i = node[i].nex) if (d[node[i].v] == d[u] + 1 and node[i].w) {
			int af = dfs(node[i].v, t, min(mn, node[i].w));
			if (af > 0) {
				flow += af;
				mn -= af;
				node[i].w -= af;
				node[i ^ 1].w += af;
				if (mn <= 0) break;
			}
		}
		return flow;
	}
	T maxflow(int s, int t) {
		T ans = 0;
		while (bfs(s, t)) {
			memcpy(cur, head, sizeof(int) * n);
			ans += dfs(s, t, numeric_limits<T>::max());
		}
		return ans;
	}
};