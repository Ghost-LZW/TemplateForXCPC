template<typename T>
struct BitTree {
	T sum[Ma];
	void add(int pos, T val) {for (; pos < Ma; pos += lowbit(pos)) sum[pos] += val;}
	T pre(int pos) {T ans = 0; for (; pos; pos -= lowbit(pos)) ans += sum[pos]; return ans;}
	T range(int l, int r) {return pre(r) - pre(l - 1);}
	void clear(int n) {memset(sum, 0, sizeof(T) * (n + 1));}
};

// Dfn 优化

struct BTDfn {
	int bit[Ma], b[Ma], T = 0;
	void add(int pos, int val) {
		for (++pos; pos < Ma; pos += lowbit(pos))
			bit[pos] = b[pos] < T ? val : max(bit[pos], val), b[pos] = T;
	}
	int sum(int pos) {
		int ans = 0;
		for (++pos; pos; pos -= lowbit(pos))
			ans = b[pos] < T ? max(ans, 0) : max(ans, bit[pos]);
		return ans;
	}
	int range(int l, int r) {return sum(r) - sum(l - 1);}
	void clear() {++T;}
} bt;