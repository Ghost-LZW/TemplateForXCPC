inline int id(int l, int r) {
	return l + r | l != r;
}

struct SegTree {
	ll ma[Ma * 2];
	void build(int l, int r, ll* my) {
		if(l == r){
			ma[id(l, r)] = max(ma[id(l, r)], my[l]);
			return ;
		}
		int mid = (l + r) >> 1;
		build(l, mid, my), build(mid + 1, r, my);
		ma[id(l, r)] = max(ma[id(l, mid)], ma[id(mid + 1, r)]);
	}
	ll querry(int l, int r, int L, int R) {
		if(l > R || r < L)return 0;
		if(L <= l && r <= R){
			return ma[id(l, r)];
		}
		int mid = (l + r) >> 1;
		return max(querry(l, mid, L, R), querry(mid + 1, r, L, R));
	}
};

struct TwTree {
	SegTree node[Ma * 2];
	void build(int l, int r) {
		if(l == r) {
			node[id(l, r)].build(1, n, de[l]);
			return ;
		}
		int mid = (l + r) >> 1;
		build(l, mid), build(mid + 1, r);
		merge(id(l, r), id(l, mid), id(mid + 1, r), 1, n);
	}
	void merge(int o, int lt, int rt, int l, int r) {
		if(l == r){node[o].ma[id(l, r)] = max(node[lt].ma[id(l, r)], node[rt].ma[id(l, r)]); return ;}
		int mid = (l + r) >> 1;
		merge(o, lt, rt, l, mid);
		merge(o, lt, rt, mid + 1, r);
		node[o].ma[id(l, r)] = max(node[o].ma[id(l, mid)], node[o].ma[id(mid + 1, r)]);
	}

	ll querry(int l, int r, int L, int R, int x1, int x2){
		if(l > R || r < L)return 0;
		if(L <= l && r <= R) {
			return node[id(l, r)].querry(1, n, x1, x2);
		}
		int mid = (l + r) >> 1;
		return max(querry(l, mid, L, R, x1, x2), querry(mid + 1, r, L, R, x1, x2));
	}
	ll querry(int x1, int y1, int x2, int y2) {
		return querry(1, n, y1, y2, x1, x2);
	}
} tw;