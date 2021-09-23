namespace SPath {
	#define qxx(i,x) for(int i = head[x]; ~i; i = node[i].nex)
	#define fep(i,b,e) for(int i=(b);i<=(e);++i)
	#define rep(i,x) for(int i=0;i<(x);++i)
	const static int Ma = 1e6;
	typedef int Dis;
	Dis inf = 0x3f3f3f3f;
	int n;
	struct Node{
		int v, nex; Dis w;
	}node[Ma * 4];
	int head[Ma], tot;
	void init(int x) {
		n = x;
		memset(head, -1, (n + 1) * sizeof(int));
		tot = 0;
	}
	void add(int u, int v, Dis w) {
		node[tot].v = v, node[tot].w = w;
		node[tot].nex = head[u], head[u] = tot++;
	}

	bool vis[Ma];
	Dis dis[Ma];

	struct cmp {
		bool operator () (int a, int b) {
			return dis[a] > dis[b];
		}
	};

	void floyd() {
		for (int k = 1; k <= n; k++)
        	for (int i = 1; i <= n; i++) if (k != i)
            	for (int j = 1; j <= n; j++) if (j != k and j != i)
                	cmin(dis[i][j], dis[i][k] + dis[k][j]);
	}

	Dis dijstra(int u, int v) {
		fep(i, 1, n)dis[i] = inf, vis[i] = false;
		dis[u] = 0;
		#ifdef GOODOJ
		__gnu_pbds::priority_queue<int, cmp> q;
		#else
		std::priority_queue<int, std::vector<int>, cmp > q;
		#endif
		q.push(u);
		while(!q.empty()) {
			int t = q.top(); q.pop();
			if(vis[t]) continue;
			vis[t] = true;
			qxx(i, t) if(!vis[node[i].v] and dis[node[i].v] > dis[t] + node[i].w)
				dis[node[i].v] = dis[t] + node[i].w, q.push(node[i].v);
		}

		return dis[v];
	}
	int time[Ma];
	Dis spfa(int u, int v) {
		fep(i, 1, n)dis[i] = inf, vis[i] = false, time[i] = 0;
		dis[u] = 0;
		#ifdef GOODOJ
		__gnu_pbds::priority_queue<int, cmp> q;
		#else
		std::priority_queue<int, std::vector<int>, cmp > q;
		#endif
		q.push(u);
		while(!q.empty()) {
			int t = q.top(); q.pop();
			vis[t] = false;
			qxx(i, t) {
				int go = node[i].v;
				if (dis[go] > dis[t] + node[i].w) {
					dis[go] = dis[t] + node[i].w;
					if(!vis[go]) {
						vis[go] = 1;
						q.push(go);
						if (++time[go] > n)
							return -1;
					}
				}
			}
		}
		return dis[v];
	}
}