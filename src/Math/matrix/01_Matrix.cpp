struct Matrix {
	static int ph;
	int r, c; int dev;
	vector<vector<int> > ma;
	Matrix (int r=1, int c=1) : r(r), c(c), dev(1) {
		ma.resize(r);
		for (int i = 0; i < r; ++i) ma[i].assign(c, 0), ma[i][i] = 1;
	}
	vector<int>& operator [] (const int& pos) {return ma[pos];}
	Matrix operator * (const Matrix& b) const {
		if (c != b.r) assert(false);
		Matrix m(r, b.c);
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < b.c; j++) {
				m.ma[i][j] = 0;
				for (int k = 0; k < c; k++)
					m.ma[i][j] += ma[i][k] * b.ma[k][j];
			}
		}
		m.cs = cs * b.cs;
		return m;
	}
	void gauss() {
		for (int i = 0, j = 0; i < r and j < c; ++j, ++i) {
			int k = i;
			for (int t = i; t < r; ++t) if (ma[t][j] != 0) {k = t; break;}
				if (ma[k][j] == 0) {--i; continue;}
			if (k != i) {
				dev = -dev;
				for (int t = 0; t < c; ++t) swap(ma[i][t], ma[k][t]);
			}
			for (int t = 0; t < r; ++t) if(t != i and ma[t][j]) {
				int d = __gcd(abs(ma[t][j]), abs(ma[i][j]));
				int p = ma[t][j] / d;
				d = ma[i][j] / d;
				for (int s = 0; s < c; ++s) (ma[t][s] *= d) -= ma[i][s] *p;
			}
		}
	}
	void print() const {
		cout << "--------------===----====---------------" << endl;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				cout << ma[i][j] << " \n"[j == c - 1];
			cout << "------------------===------------------" << endl;
	}
};


// 已知大小 带编译期间检测

template<int r, int c, typename val_type=ll>
struct mat {
    array<array<val_type, c>, r> res;
    const static int cr=r, cc=c;
    void fill(const array<val_type, r * c>& val) {
        rep (i, r) rep (j, c) res[i][j] = val[i * c + j] % mod;
    }
    void fill() {
        rep (i, r) rep (j, c) res[i][j] = i == j;
    }
    template<typename T>
    mat<r, T::cc> operator * (const T& val) {
        assert(c == T::cr);
        mat<r, T::cc> tp;
        rep (i, r) rep (j, T::cc) {
            tp[i][j] = 0;
            rep (k, c) (tp[i][j] += (res[i][k] * val[k][j] % mod)) %= mod;
        }
        return tp;
    }
	mat<r, c> operator + (const mat<r, c>& b) const {
		mat<r, c> tp;
		rep (i, r) rep (j, c)
			tp[i][j] = (res[i][j] + b[i][j]) % mod;
		return tp;
	}
	mat<r, c> operator ^ (ll b) {
		mat<r, c> s, t; s.fill();
		t = *this;
		for (; b; b >>= 1, t = t * t)
			if (b & 1) s = s * t;
		return s;
	}	
    array<val_type, c>& operator [] (const int& pos) {
        return res[pos];
    }
    const array<val_type, c>& operator [] (const int& pos) const {
        return res[pos];
    }
	void print() const {
		cout << "=== matrix ===" << endl;
		rep (i, r) {
			rep (j, c) cout << res[i][j] << ' ';
			cout << endl;
		}
		cout << "==============" << endl;
	}
};
