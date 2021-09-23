/**
人I - A 特征多项式 p[0] * x0 + p[1] * x1 + p[2] * x2 ...
**/
namespace Characteristic {
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	const u32 P = 998244353;

	u32 add_mod(u32 x, u32 y) { return x + y >= P ? x + y - P : x + y; }
	u32 sub_mod(u32 x, u32 y) { return int(x - y) < 0 ? x + P - y : x - y; }
	u32 mul_mod(u32 x, u32 y) { return u64(x) * y % P; }
	u32 norm_mod(int x) { return x %= int(P), (x < 0 ? x + P : x); }
	u32 pow_mod(u32 x, int y) {
	  u32 res = 1;
	  for (; y; y >>= 1, x = mul_mod(x, x))
	    if (y & 1) res = mul_mod(res, x);
	  return res;
	}
	u32 inv_mod(u32 x) { return pow_mod(x, P - 2); }

	std::vector<std::vector<u32>> input() {
	  int n;
	  std::cin >> n;
	  std::vector<std::vector<u32>> a(n, std::vector<u32>(n));
	  for (auto &r : a)
	    for (auto &c : r) std::cin >> c;
	  return a;
	}

	std::vector<std::vector<u32>> reduce(std::vector<std::vector<u32>> m) {
	  int n = m.size();
	  if (n <= 2) return m;
	  for (int i = 0; i != n - 2; ++i) {
	    int p = i + 1;
	    { // 选取主对角线下方最大的元素（因为是模素数意义下于是非零即可）
	      for (; p != n; ++p)
	        if (m[p][i] != 0) break;
	    }
	    if (p == n) continue;        // 下方全是零，无需消元
	    if (p != i + 1) {            // 为了相似变换，需要交换对应行和列
	      std::swap(m[p], m[i + 1]); // 交换行
	      for (int j = 0; j != n; ++j) std::swap(m[j][p], m[j][i + 1]); // 交换列
	    }
	    u32 iv = inv_mod(m[i + 1][i]);
	    for (int j = i + 2; j != n; ++j) {
	      u32 v = mul_mod(m[j][i], iv);
	      for (int k = 0; k != n; ++k) m[j][k] = sub_mod(m[j][k], mul_mod(v, m[i + 1][k]));
	      for (int k = 0; k != n; ++k) m[k][i + 1] = add_mod(m[k][i + 1], mul_mod(v, m[k][j]));
	    }
	  }
	  return m;
	}

	std::vector<u32> mul_poly(const std::vector<u32> &x, const std::vector<u32> &y) {
	  int n = x.size(), m = y.size();
	  std::vector<u32> res(n + m - 1, 0);
	  for (int i = 0; i != n; ++i)
	    for (int j = 0; j != m; ++j) res[i + j] = add_mod(res[i + j], mul_mod(x[i], y[j]));
	  return res;
	}

	std::vector<u32> get_charpoly(const std::vector<std::vector<u32>> &h) { // h 为一个上海森堡矩阵
	  int n = h.size();
	  std::vector<std::vector<u32>> p(n + 1);
	  p[0] = {1};
	  p[1] = {norm_mod(-h[0][0]), 1};
	  for (int i = 2; i <= n; ++i) {
	    p[i] = mul_poly(p[i - 1], {norm_mod(-h[i - 1][i - 1]), 1});
	    for (int j = 1; j <= i - 1; ++j) {
	      u32 prod = h[i - 1 - j][i - 1];
	      for (int k = i; k >= i - j + 1; --k) prod = mul_mod(prod, h[k - 1][k - 2]);
	      for (int k = 0; k <= i - j - 1; ++k)
	        p[i][k] = sub_mod(p[i][k], mul_mod(prod, p[i - j - 1][k]));
	    }
	  }
	  return p[n];
	}
}

rap (i, Characteristic::get_charpoly(Characteristic::reduce(Characteristic::input()))) cout << i << ' ';