struct SegTree {
	long sum[Ma << 2], lazy[Ma << 2];
	SegTree() {memset(sum, 0, sizeof sum);memset(lazy, 0, sizeof lazy);}
	void add(int o, int l, int r, int L, int R, int val) {
		if (r < L or R < l) return ;
		if(L <= l and r <= R) {
			lazy[o] += val;
			sum[o] += (ll) (r - l + 1) * val;
			return ;
		}
		int mid = (l + r) >> 1;
		if (lazy[o] and l != r) {
			sum[o << 1] += lazy[o] * (mid - l + 1);
			sum[o << 1 | 1] += lazy[o] * (r - mid);
			lazy[o << 1] += lazy[o];
			lazy[o << 1 | 1] += lazy[o];
			lazy[o] = 0;
		}
		add(o << 1, l, mid, L, R, val);
		add(o << 1 | 1, mid + 1, r, L, R, val);
		sum[o] = sum[o << 1] + sum[o << 1 | 1];
	}
	int querry(int o, int l, int r, int pos){
		if(l == r) return sum[o];
		int mid = (l + r) >> 1;
		if (lazy[o] and l != r) {
			sum[o << 1] += lazy[o] * (mid - l + 1);
			sum[o << 1 | 1] += lazy[o] * (r - mid);
			lazy[o << 1] += lazy[o];
			lazy[o << 1 | 1] += lazy[o];
			lazy[o] = 0;
		}
		if (pos <= mid) return querry(o << 1, l, mid, pos);
		else return querry(o << 1 | 1, mid + 1, r, pos);
	}
} st;