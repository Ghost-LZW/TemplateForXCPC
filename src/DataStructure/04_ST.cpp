template<typename T>
struct ST {
	static const int K = 25;
	static const int Ma = 1e6;
	int log[Ma + 1];
	T st[Ma][K + 1];
	ST() {
		log[1] = 0;
		for (int i = 2; i <= Ma; i++)
			log[i] = log[i / 2] + 1;
	}
	void build(T* ary, int N, T (*f)(T, T)) {
		for (int i = 0; i < N; i++)
			st[i][0] = ary[i];
		for (int j = 1; j <= K; j++)
			for (int i = 0; i + (1 << j) <= N; i++)
				st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}
	T querry(int l, int r, T (*f)(T, T)) {
		int j = log[r - l + 1];
		return f(st[l][j], st[r - (1 << j) + 1][j]);
	}
	T sum(int l, int r) {
		T sum = 0;
		for (int j = K; j >= 0; j--)
			if ((1 << j) <= r - l + 1)
				sum += st[l][j], l += (1 << j);
		return sum;
	}
};