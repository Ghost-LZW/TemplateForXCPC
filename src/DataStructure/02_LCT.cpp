struct LCT {
	#define lc(x) T[x].ch[0]
	#define rc(x) T[x].ch[1]
	#define fa(x) T[x].fa
	#define root T[0].ch[1]
	const static int Ma = 1e6;
	struct Node{
		int fa, v, ch[2], lazy, size, ans;
		void swap() {
			std::swap(ch[0], ch[1]);
			lazy ^= 1;
		}
	} T[Ma];
	int tot;
	int ident(int x){return T[fa(x)].ch[0] == x ? 0 : 1;}
	void connnet(int a, int f, int h){fa(a) = f, T[f].ch[h] = a;}
	bool isroot(int x) {return !fa(x) or (lc(fa(x)) != x and rc(fa(x)) != x);}
	void rotate(int x) {
		int y = fa(x), r = fa(y);
		pushdown(y), pushdown(x);
		int ys = ident(x), rs = ident(y);
		connnet(T[x].ch[ys ^ 1], y, ys);
		if (isroot(y)) fa(x) = r;
		else connnet(x, r, rs);
		connnet(y, x, ys ^ 1);
		update(y), update(x);
	}
	void splay(int x) {
		pushdown(x);
		for(; !isroot(x); rotate(x))
			if(!isroot(fa(x))) rotate(ident(x) == ident(fa(x)) ? fa(x) : x);
	}
	void access(int x) {
		for (int p = 0; x; x = fa(p = x))
			splay(x), rc(x) = p, update(x); // 维护虚儿子在此处修改
	}
	void makeRoot(int x) {
		access(x);
		splay(x);
		T[x].lazy ^= 1;
	}
	int findRoot(int x) {
		access(x);
		splay(x); pushdown(x);
		while (lc(x)) x = lc(x), pushdown(x);
		splay(x);
		return x;
	}
	void link(int x, int p) {
		makeRoot(x);
		if (findRoot(p) == x) return ;
		fa(x) = p; // 维护虚儿子splay p ，更新信息
	}
	void cut(int x, int y) {
		makeRoot(x);
		if (findRoot(y) != x or fa(y) != x or lc(y)) return ;
		fa(y) = rc(x) = 0;
		update(x);
	}
	void split(int x, int y) {
		makeRoot(x);
		access(y);
		splay(y);
	}
	void pushdown(int x) {
		if(x && T[x].lazy) {
			T[lc(x)].lazy ^= 1;
			T[rc(x)].lazy ^= 1;
			T[x].swap();
		}
	}

	void update(int x) {
		if (x) T[x].size = T[lc(x)].size + T[rc(x)].size + 1,
		       T[x].ans = T[x].v ^ T[lc(x)].ans ^ T[rc(x)].ans;
	}

	int newpoint(int v, int f=0){
		T[++tot].fa = f;
		T[tot].v = v;
		T[tot].size = 1;
		return tot;
	}

	int build(int l, int r, int f){
		if(l > r)return 0;
		int mid = (l + r) >> 1;
		int now = newpoint(mid, f);
		lc(now) = build(l, mid - 1, now);
		rc(now) = build(mid + 1, r, now);
		update(now);
		return now;
	}

	int find(int x){
		for(int now = root; ;){
			pushdown(now);
			if(x <= T[lc(now)].size)now = lc(now);
			else {
				x -= T[lc(now)].size + 1;
				if(!x)return now;
				now = rc(now);
			}
		}
		return 0;
	}

	void show(int me, int n) {
		if (!me) return ;
		pushdown(me);
		show(lc(me), n);
		if(T[me].v != 0 && T[me].v != n + 1){
			printf("%d ", me);
		}
		show(rc(me), n);
	}

	void change(int x, int y) {
		splay(x);
		T[x].v = y;
	}

	Node& operator [] (const int& i) {
		return T[i];
	}
} lct;
