struct Splay{
	#define lc(x) T[x].ch[0]
	#define rc(x) T[x].ch[1]
	#define fa(x) T[x].fa
	#define root T[0].ch[1]
	const static int Ma = 1e6;
	struct Node{
		int fa, v, ch[2], lazy, size;
		void swap() {
			int t = ch[0];
			ch[0] = ch[1];
			ch[1] = t;
		}
	} T[Ma];
	int tot;
	int ident(int x){return T[fa(x)].ch[0] == x ? 0 : 1;}
	void connnet(int a, int f, int h){fa(a) = f, T[f].ch[h] = a;}
	void rotate(int x){
		int y = fa(x), r = fa(y);
		pushdown(y), pushdown(x);
		int ys = ident(x), rs = ident(y);
		connnet(T[x].ch[ys ^ 1], y, ys);
		connnet(y, x, ys ^ 1);
		connnet(x, r, rs);
		update(y), update(x);
	}
	void splay(int x, int to){
		for(to = fa(to); fa(x) != to; rotate(x))
			if(fa(fa(x)) != to)rotate(ident(x) == ident(fa(x)) ? fa(x) : x);
	}

	void update(int x){
		if(x)T[x].size = T[lc(x)].size + T[rc(x)].size + 1;
	}

	int newpoint(int v, int f){
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

	void Revers(int l, int r){
		splay(find(l - 1), root);
		splay(find(r + 1), rc(root));
		T[lc(rc(root))].lazy ^= 1;
	}

	void pushdown(int x){
		if(x && T[x].lazy){
			T[lc(x)].lazy ^= 1;
			T[rc(x)].lazy ^= 1;
			T[x].swap();
			T[x].lazy = 0;
		}
	}

	void show(int me){
		if(!me)return ;
		pushdown(me);
		show(lc(me));
		if(T[me].v != 0 && T[me].v != n + 1){
			printf("%d ", T[me].v);
		}
		show(rc(me));
	}
}tr;
